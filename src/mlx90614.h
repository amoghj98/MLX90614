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

#ifndef _TEMP_SCANNER_
#define _TEMP_SCANNER_

/***************************************************************************************************************************************
	
	Arduino Library for Melexis MLX90614 IR Temperature sensor
	NOTE :	The MLX90614 uses a derivative of the I2C standard called SMBus, which only permits a single bus master.
			It also requires the use of an uncommon signalling technique called "repeated start", which involves repeatedly sending
			START signals on the bus. All Arduino boards are compatible with this signalling scheme. However, if not using an Arduino,
			please verify your microcontroller's ability to support such signalling before using this library.

***************************************************************************************************************************************/

#define devid 0x5A				// I2C slave address

/***************************************************************************************************************************************

	All EEPROM and RAM register addresses are pre-orred with their respective access opcodes.
	No explicit orring is therefore required in the data transaction functions
	For details on these opcodes, refer Page 20 of the datasheet

***************************************************************************************************************************************/

// EEPROM addresses
#define obj_temp_max 0x20
#define obj_temp_min 0x21
#define pwmctrl 0x22
#define ambient_temp_range 0x23
#define emissivity 0x24
#define config1 0x25
#define smbus_add_lsb 0x2E

// RAM addresses
#define ambient_temp 0x06
#define obj_temp1 0x07
#define obj_temp2 0x08

// clock frequency and special opcodes
#define mlx_clk 50000
#define read_flags 0xF0
#define sleep_mode 0xFF

class mlx90614
{
private:
	uint8_t gen_crc8(uint8_t *address, uint8_t size);
	uint8_t write_data(uint8_t address, uint16_t data);
	uint16_t read_data(uint8_t address);
	float read_temperature(uint8_t address);
public:
	uint8_t init();
	float read_obj_temp_degK();
	float read_obj_temp_degC();
	float read_ambient_temp_degK();
	float read_ambient_temp_degC();
	uint8_t set_emissivity(double em);
	double get_emissivity();
};

#endif