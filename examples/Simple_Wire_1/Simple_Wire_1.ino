/*
 * Define SHT_Wire_1 for use with Wire1 or SHT_Wire_2 for use with Wire2.
 * With no defines, the basic Wire will be used.
 */

#define SHT_Wire_1
#include <SHT3x.h>
SHT3x Sensor;
void setup() {
  
  Serial.begin(19200);
  Sensor.Begin();
}

void loop() {

  Sensor.UpdateData();
  Serial.print("Temperature: ");
  Serial.print(Sensor.GetTemperature());
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.println("C");
  Serial.print("Humidity: ");
  Serial.print(Sensor.GetRelHumidity());
  Serial.println("%");

  delay(333);
}
