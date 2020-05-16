/**************************************************************************************************************************

    Example Arduino code to print the temperature of the object the MLX90614 trained at once every second.
    
**************************************************************************************************************************/

#include "mlx90614.h"

class mlx90614 tempscanner;

float t;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tempscanner.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  t=tempscanner.read_obj_temp_degC();
  Serial.print("Object Temperature: ");
  Serial.println(t);
  delay(1000);
}
