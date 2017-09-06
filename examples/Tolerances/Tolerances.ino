/*
 * Sometimes you are interesting not in the only values of measurable parameters, 
 * but in their tolerances too.
 * This library supports tolerances for temperature, relative and absolute humidity 
 * in all scales you can found in corresponding examples.
 * 
 * Tolerances are in dependence from ambient temperature and humidity and sensor model. 
 * Accuracy grows with a sensor model number: SHT30<SHT31<SHT35.
 * 
 * Tolerances dependence for different temperature and humidity range got from the datasheet/section 1/
 */


#include <SHT3x.h>
SHT3x Sensor; //The default sensor type is SHT30
void setup() {
  
  Serial.begin(19200);
  Sensor.Begin();
}

void loop() {
  Sensor.UpdateData();
  Serial.print("Temperature: ");
  Serial.print(Sensor.GetTemperature(),1); //Celsius
  Serial.print(" ± ");
  Serial.print(Sensor.GetTempTolerance(),1);
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("C");

  Serial.println();

  Serial.print("Relative humidity: ");
  Serial.print(Sensor.GetRelHumidity(),1);
  Serial.print(" ± ");
  Serial.print(Sensor.GetRelHumTolerance(),1);
  Serial.print("%");

  Serial.println();

  Serial.print("Absolute humidity: ");
  Serial.print(Sensor.GetAbsHumidity(SHT3x::Pa),1); //Pascal, for example
  Serial.print(" ± ");
  Serial.print(Sensor.GetAbsHumTolerance(SHT3x::Pa),1);
  Serial.print(" Pa");  

  Serial.println();
  delay(333);
}
