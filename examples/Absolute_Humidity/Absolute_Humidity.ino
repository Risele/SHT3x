/*
 * Processes in Nature (not the journal) does not takes _relative_ humidity into account.
 * They takes into account _absolute_ humidity (water vapor pressure).
 * So, that library supports vapor pressure calculation.
 * All pressure scales I found in Wikipedia are available:  
 *    mmHg, Torr,
      Pa,   Bar,
      At    (Techical atmosphere),
      Atm   (Standart atmosphere),
      mH2O, //O is the letter, not zero
      psi,
 * (check SHT3x.h, "enum AbsHumidityScale").
 * The absolute humidity tolerance could be recieved in same scales too.
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
  
  Serial.print(Sensor.GetRelHumidity());
  Serial.print("%");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity()); //Torr by default
  Serial.print(" Torr");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity(SHT3x::psi)); //Torr by default
  Serial.print(" psi");
  Serial.print(" | ");

  Serial.print(Sensor.GetAbsHumidity(SHT3x::Pa)); //Torr by default
  Serial.print(" Pa");

  //And other...

  Serial.print(" Tolerance: ±");
  Serial.print(Sensor.GetAbsHumTolerance(SHT3x::mH2O));
  Serial.print(" mH2O");
  

  Serial.println();
  delay(333);
}
