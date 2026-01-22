## Arduino library for Sensirion temperature and humidity sensors SHT30, SHT31 & SHT35.

Check for /examples for examples of different use cases.

The datasheet I followed is:
https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf

The constructor structure:
```Cpp
SHT3x(	int Address = 0x44, //I2C device address, 0x44 or 0x45
                ValueIfError Value = Zero, //What to return in case of errors. Zero or PrevValue
                uint8_t HardResetPin = 255, //Number of pin RESET connected to (input from 100 to 255 if not used)
                SHT3xSensor SensorType = SHT30, //Sensor type, SHT30, SHT31 or SHT35.
                SHT3xMode Mode=Single_HighRep_ClockStretch //Operation mode , look for "enum SHT3xMode"
                ); 
```

#### Supports:
- Temperature data at Celsius, Kelvin and Fahrenheit scales.
- Relative humidity data.
- Absolute humidity data at Torr, mm Hg, Pa, bar, technical and standard atmosphere, psi scales.
- Data integrity (by CRC8 algorithm) (datasheet/section 4.12).
- Temperature, relative and absolute humidity tolerances (in dependence from measured values)
- Calibration (linear) of temperature and humidity data by factors or by reverse sensor values (2 points)
- Heater On/Off (integrated to SHT3x sensor) (datasheet/section 4.10)
- Different sensor actions modes (datasheet/section 4.3)
- Reset: soft (I2C) and hard (by corresponding pin) (datasheet/section 4.9)

#### Do not supports:
- Action in periodic mode (datasheet/section 4.5)
- Interrupts (datasheet/section 3.5)
- Aler mode

> [!WARNING]	
> Wire1/2 support updated.
> Your code may change since SDA pin usage removed.

For using with Wire1/Wire2 #define **BEFORE** importing library:
``` C
#define SHT_Wire_1 //For Wire1
//OR (not both)
#define SHT_Wire_2 //For Wire2
```
Wire is used by default

- Note 1: by default, the data from sensor updates not faster, than 2 times a second.
For faster update use SetUpdateInterval(uint32_t UpdateIntervalMillisec); but do not exceed the datasheet values (10 measurments per second (100 ms)) because of sensor self-heating (datasheet/section 4.5, at the end of Table 9)

- Note 2: The sensor type affects the tolerance values only. 

