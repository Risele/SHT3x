/*
 * 3 temperature scales are available:
 * Celsius (default)
 * Fahrenheit
 * Kelvin
 */


#include <SHT3x.h>
SHT3x Sensor;
void setup() {
  
  Serial.begin(19200);
  Sensor.Begin();
}

void loop() {
  Sensor.UpdateData();
  
  Serial.print(Sensor.GetTemperature()); //Celsius
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("C");
  Serial.print(" | ");
  
  Serial.print(Sensor.GetTemperature(SHT3x::Cel)); //Celsius again
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("C");
  Serial.print(" | ");

  Serial.print(Sensor.GetTemperature(SHT3x::Far)); //Fahrenheit
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("F");
  Serial.print(" | ");

  Serial.print(Sensor.GetTemperature(SHT3x::Kel)); //Kelvin again
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("K");
  

  Serial.println();
  delay(333);
}
