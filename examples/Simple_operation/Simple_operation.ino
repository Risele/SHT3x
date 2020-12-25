/*
 * The simplest operation using SHT3x
 */

#include <SHT3x.h>
SHT3x Sensor;
SHT3x Sensor2;

#define SCL_2 17
#define SDA_2 16

void setup() {
Serial.begin(115200);
Sensor.Begin();
Sensor2.Begin(SDA_2,SCL_2);
}
void loop() {
Sensor.UpdateData();
Sensor2.UpdateData(SDA_2);

Serial.print("Temperature: ");
Serial.print(Sensor.GetTemperature());
Serial.write("\xC2\xB0"); //The Degree symbol
Serial.print("C, ");
Serial.print("Humidity: ");
Serial.print(Sensor.GetRelHumidity());
Serial.println("%");

Serial.print("Temperature: ");
Serial.print(Sensor2.GetTemperature());
Serial.write("\xC2\xB0"); //The Degree symbol
Serial.print("C, ");
Serial.print("Humidity: ");
Serial.print(Sensor2.GetRelHumidity());
Serial.println("%");

Serial.println("");
delay(333);
}
