/*\
 * Changing data update frequency (check for Note 1 in SHT3x.h)
 */


#include <SHT3x.h>
SHT3x Sensor_FAST;
SHT3x Sensor_SLOW(0x45); //Set the address by hands
void setup() {

    Serial.begin(19200);
    Sensor_FAST.SetUpdateInterval(100);     //Data will be updated 10 times per seconds
    Sensor_SLOW.SetUpdateInterval(10*1000); //Data will be updated 1 time per 10 seconds
    Sensor_FAST.Begin();
    Sensor_SLOW.Begin();
}

void loop() {
    
    Sensor_FAST.UpdateData();
    Sensor_SLOW.UpdateData();

    Serial.println("Temperature, \xC2\xB0C");
    Serial.print("F: "); Serial.print(Sensor_FAST.GetTemperature(),2);
    Serial.print(" | ");
    Serial.print("S: "); Serial.print(Sensor_SLOW.GetTemperature(),2);
    Serial.println();
    
    Serial.println("Relative Humidity, %");
    Serial.print("F: "); Serial.print(Sensor_FAST.GetRelHumidity(),2);
    Serial.print(" | ");
    Serial.print("S: "); Serial.print(Sensor_SLOW.GetRelHumidity(),2);
  delay(333);
}
