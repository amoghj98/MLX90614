<h2><b>Arduino Library for MLX90614 IR Temperature Sensor</b></h2>
This is a general-purpose library for the Melexis MLX90614 contactless IR Temperature sensor.<br><br>
Author : Amogh S. Joshi<br>
Link : <a href="https://github.com/amoghj98/MLX90614">https://github.com/amoghj98/MLX90614</a>

<h2><b>License</b></h2>
The use of this library is subject to the MIT license.
<h2><b>Description</b></h2>
The Melexis MLX90614 is an Infra Red thermometer for noncontact temperature measurements. Both the IR sensitive thermopile detector chip and the signal conditioning ASSP are integrated in the same TO-39 can. The MLX90614 supports a derivative of the I2C bus called SMBus. SMBus was initially meant for low-bandwidth communication between devices on the same motherboard. The MLX90614 supports SMBus communication with clock frequencies ranging from 10kHz to 100kHz. The tech specs of the MLX90614 are as follows:
<table>
  <tr>
    <th>Parameter</th>
    <th>Value</th>
  </tr>
  <tr>
    <td>SMBus Clock Frequency</td>
    <td>10kHz - 100kHz</td>
  </tr>
  <tr>
    <td>Resolution (while using SMBus protocol)</td>
    <td>0.02°C</td>
  </tr>
  <tr>
    <td>Ambient Temperature Range</td>
    <td>-40°C - 125°C</td>
  </tr>
  <tr>
    <td>Object Temperature Range</td>
    <td>-70°C - 380°C</td>
  </tr>
</table>

<h2><b>Usage</b></h2>
The library contains the following functions:
<h4>Object Declaration</h4>

```C++
mlx90614 tempscanner;
```
<h4>Configuration Function</h4>
<b>init()</b> This function initialises the SMBus and also (optionally) changes the value of emmisivity stored in the emmisivity register

```C++
uint8_t t = tempscanner.init();
```
<h4>Data Collection Functions</h4>
<b>read_obj_temp_degK()</b> This function reads the object temperature in degrees Kelvin.<br>

```C++
float obj_temp_K = tempscanner.read_obj_temp_degK();
```
<b>read_obj_temp_degC()</b> This function reads the object temperature in degrees Celcius.<br>

```C++
float obj_temp_C = tempscanner.read_obj_temp_degC();
```
<b>read_ambient_temp_degK()</b> This function reads the ambient temperature in degrees Kelvin.<br>

```C++
float amb_temp_K = tempscanner.read_ambient_temp_degK();
```
<b>read_ambient_temp_degC()</b> This function reads the ambient temperature in degrees Celcius.<br>

```C++
float amb_temp_C = tempscanner.read_ambient_temp_degC();
```
<b>get_emissivity()</b> This function reads the value stored in the emmisivity register, pre-processes it (by dividing by 65535 and converting to double) and returns the processed value.

```C++
double em = tempscanner.get_emissivity();
```
<h4>Data Setting Function</h4>
<b>set_emissivity(double em)</b> This function changes the value in the emmisivity register to a user-defined value. This value is 65535 times the input argument em, converted to a 16-bit unsigned integer.<br>

```C++
uint8_t res = tempscanner.set_emissivity(0.2675);
```
