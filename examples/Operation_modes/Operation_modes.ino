/*
 * Different data acquisition modes.
 * The repeatability affects on measurment duration (datasheet/section 2.2):
 * Low      -> 2.5 ms
 * Medium   -> 4.5 ms
 * High     -> 12.5 ms
 */

#include <SHT3x.h>

SHT3x Sensor_H(0x44); //Set the sensor address for HIGH repeatablity 
//SHT3x Sensor_L(0x45,SHT3x::Single_LowRep_ClockStretch); //The repeatability is not often usable option,
//I think, so I put it to the end of constuctor. So, because we need to define all options, let's do it:
SHT3x Sensor_L( 0x45,         //Set the address
                SHT3x::Zero,  //Functions will return zeros in case of error
                255,          //If you DID NOT connected RESET pin
                SHT3x::SHT30, //Sensor type
                SHT3x::Single_LowRep_ClockStretch //Low repetability mode
                );
              

void setup() {
    Serial.begin(19200);
    Sensor_H.Begin();
    Sensor_L.Begin();

}

void loop() {
    Sensor_H.UpdateData();
    Sensor_L.UpdateData();
    Serial.println("Temperature, \xC2\xB0C");
    Serial.print("H: "); Serial.print(Sensor_H.GetTemperature(),2);
    Serial.print(" | ");
    Serial.print("L: "); Serial.print(Sensor_L.GetTemperature(),2);
    Serial.println();
    
    Serial.println("Relative Humidity, %");
    Serial.print("H: "); Serial.print(Sensor_H.GetRelHumidity(),2);
    Serial.print(" | ");
    Serial.print("L: "); Serial.print(Sensor_L.GetRelHumidity(),2);
    delay(333);
}
