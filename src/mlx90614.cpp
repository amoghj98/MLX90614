/***************************************************************************************************************************************

	©2020, Amogh S. Joshi. Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
	documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
	is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

***************************************************************************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include "mlx90614.h"

/************************************************************************************************************************************

	Private functions for low-level hardware interaction
	CAUTION : Manipulation of these functions may lead to system malfunctions

*************************************************************************************************************************************/

uint8_t mlx90614::gen_crc8(uint8_t *address, uint8_t size)
{
	/*
		Function to generate the CRC-8 checksum to be transmitted while performing a write to EEPROM or RAM.
		CRC polynomial = x8 + x2 + x + x0
		Refer to Page 19 of the datasheet for more details
	*/
	uint8_t crc = 0;
	while (size--)
	{
		uint8_t in_word = *address++;
		for (uint8_t i = 8; i; i--)
		{
			uint8_t carry = (crc ^ in_word) & 0x80;
			crc <<= 1;
			if (carry)
				crc ^= 0x7;
			in_word <<= 1;
		}
	}
	return crc;
}

uint8_t mlx90614::write_data(uint8_t address, uint16_t data)
{
	/*
		Function to write 16-bit data to memory
		Refer to timing diagram on Page 20 of the datasheet for more details.
	*/
	uint8_t pec, pec_buf[4];
	uint8_t dl=(data & 0xFF), dh=data>>8;
	pec_buf[0] = devid << 1;
	pec_buf[1] = address;
	pec_buf[2] = dl;
	pec_buf[3] = dh;
	pec = gen_crc8(pec_buf, sizeof(pec_buf));
	Wire.beginTransmission(devid);
	Wire.write(address);
	Wire.write(dl);
	Wire.write(dh);
	Wire.write(pec);
	Wire.endTransmission(true);
	return 0;
}

uint16_t mlx90614::read_data(uint8_t address)
{
	/*
		Function to read 16-bit data from memory
		CAUTION : The read operation requires a repeated START condition on the bus. Refer to Page 19 and 20 of the datasheet for more details.
	*/
	uint16_t data;
	Wire.beginTransmission(devid);
	Wire.write(address);
	Wire.endTransmission(false);	// Transmit slave and register addresses to the sensor, followed by a repeated START condition.
	Wire.requestFrom(devid, 3);
	data=Wire.read();				// Data is received in LSByte-first order.
	data|=(Wire.read()<<8);
	uint8_t pec=Wire.read();		// An 8-bit PEC follows the 16-bit data. For the significance of the bits in the PEC, refer to Page 20
	return data;
}

/************************************************************************************************************************************

	Intermediate Function
	Reads temperature and converts to degK. Included to avoid code repetition
	May be used directly to reduce code footprint

*************************************************************************************************************************************/

float mlx90614::read_temperature(uint8_t address)
{
	float t=read_data(address);
	t*=0.02;
	return t;
}

/************************************************************************************************************************************

	Public functions
	Meant for user system interaction with the MLX90614

*************************************************************************************************************************************/

uint8_t mlx90614::init()
{
//  double em=0.3;      // User-defined emmisivity value to be set into the emmisivity register
	Wire.begin();
//	set_emissivity(em);   // Rewrite emmisivity register with user-defined emmisivity value.
	return 0;
}

float mlx90614::read_obj_temp_degK()
{
	return read_temperature(obj_temp1);
}

float mlx90614::read_obj_temp_degC()
{
	return read_temperature(obj_temp1) - 273.15;
}

float mlx90614::read_ambient_temp_degK()
{
	return read_temperature(ambient_temp);
}

float mlx90614::read_ambient_temp_degC()
{
	return read_temperature(ambient_temp) - 273.15;
}

uint8_t mlx90614::set_emissivity(double em)
{
	/*
		Pre-processing is as suggested on Page 14 of the datasheet
		An erase cycle (write '0') is required before the emissivity register is modified (Refer Page 14 of the datasheet)
		A delay of atleast 5ms must be inserted post EEPROM write to ensure data coherence (Refer Page 17 of the datasheet)
	*/
	uint16_t e=(uint16_t)(0xFFFF*em);	
	write_data(emissivity, e);
	delay(10);
	return 0;
}

double mlx90614::get_emissivity()
{
	return (double)read_data(emissivity)/65535.0;
}
