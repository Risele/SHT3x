/*
 * The simplest operation using SHT3x
 */


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
