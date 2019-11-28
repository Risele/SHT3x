/*
 * If you found that your sensor is not well-calibrated, you can overcalibrate it (with linear function).
 * Calibration translates values recieved from your SHT3x to data that your reference sensor recievs under the same conditions.
 * You can overcalibrated both temperature and relative humidity independently.
 * Note, that temperature calibration use CELSIUS for overcalculate data:
 *  FIRST, the temperature converts from sensor byte data to Celsius (check SHT3x::UpdateData),
 *  SECOND, temperature scales up in respect to calibration.
 *  THIRD, temperature converts from Celsius to your scale
 *  You can check SHT3x.cpp, SHT3x::UpdateData and SHT3x::GetTemperature for more information.
 *  Example for non-celsius scales located at the row 71.
 * The same is for relative humidity.
 * 
 * There are two ways for overcalibration: by Factors and by Points.
 * By Factors means, that you precalculated your calibration,
 * and by Points means, that you have set of TWO experimental points you get from your STH3x and reference sensors.
 * The calibration works this way:
 * Calibrated_Value = Non_Calibrated_Value * Factor + Shift.
 * 
 * There are two special struct'ures for the calibration needs:
 *  struct CalibrationFactors
 *  {
 *    CalibrationFactors():Factor(1.), Shift(0.){} //predefine values
 *    float Factor;
 *    float Shift;
 *  };
 * 
 * and
 * 
 * struct CalibrationPoints
 * {
 *  float First;
 *  float Second;
 * };
 * 
 * For example, let's overcalibrate our sensor:
 *  by points for relative humidity
 * and
 *  by factors for temperature
 */


#include <SHT3x.h>
SHT3x Sensor; //This operates in Celsius
SHT3x Sensor_Far(0x45); //This operates in Fahrenheit
void setup() {
  SHT3x::CalibrationPoints HumidityReference; //Points from reference sensor
  SHT3x::CalibrationPoints HumiditySHT; //Points from your SHT3x sensor
  HumidityReference.First = 0.; //If you really could achieve those ambient conditions, please, call me 8-800-355-...
  HumidityReference.Second = 100.;
  HumiditySHT.First = 5.3;
  HumiditySHT.Second = 97.;
  Sensor.SetRelHumidityCalibrationPoints(HumiditySHT, HumidityReference);

  SHT3x::CalibrationFactors TemperatureCalibration;
  TemperatureCalibration.Factor = -1.;
  TemperatureCalibration.Shift = -1000.;
  /*And than use Kelvin, muhaha!
  Ok, that was a joke. Here are real values from my expeirence (Celsius):
  my SHT30 and trusted instrument have shown 
  (temperature conditions were similar, we tested it over humidity changes):
  SHT30: 23.6 ; 25.1;
  TrIns: 22.3 ; 23.7;
  So, the overcalibraion equation is:
  Trusted_Instrument = SHT30 * 0.9333 + 0.2733,
  so 
  */
  TemperatureCalibration.Factor = 0.9333; 
  TemperatureCalibration.Shift  = 0.2733;
  Sensor.SetTemperatureCalibrationFactors(TemperatureCalibration);

  /* FOR OTHER TEMPERATURES SCALES
   * First, you have to convert data you use for calibration to Celsius.
   * For example, if I use Fahrenheit in both SHT and reference sensors and got the next data set:
   * SHT  Ref //Fahrenheit
   * 32   35
   * 50   52
   * 167  180
   * I have to convert it to Celsius:
   * SHT  Ref //Celsius
   * 0    1.7
   * 10   11.1
   * 75   82.2
   * For this particular dataset overcalibration is the following (linear approximation by Microsoft Excel):
   */
  TemperatureCalibration.Factor = 1.0807; //We have already set calibration for Celsius sensor,
  TemperatureCalibration.Shift  = 1.0467; //so, there is no need for a new variable
  Sensor_Far.SetTemperatureCalibrationFactors(TemperatureCalibration);
  Serial.begin(19200);
  Sensor.Begin();
  Sensor_Far.Begin();
}

void loop() {
  Sensor.UpdateData();
  
  Serial.print(Sensor.GetTemperature()); //Celsius
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("C");
  Serial.print(" | ");
  
  Serial.print(Sensor.GetRelHumidity()); 
  Serial.write("%");
  
  //And, for an Fahreneit sensor:
  Sensor_Far.UpdateData();
  Serial.print(Sensor_Far.GetTemperature(SHT3x::Far));
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("F");
  Serial.println();
  delay(333);
}
