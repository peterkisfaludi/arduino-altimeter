#include <Arduino.h>
#include <Wire.h>
//#include <EEPROM.h>
#include <avr/eeprom.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
#define update_eeprom_word(address,value) eeprom_update_word ((uint16_t*)address,(uint16_t)value)

//declare an eeprom array
uint16_t EEMEM  my_eeprom_array[510];

// declare a ram array
//unsigned int my_ram_array[10];

/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2013/JUN/17  - Updated altitude calculations (KTOWN)
   2013/FEB/13  - First version (KTOWN)
*/

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

static uint16_t eepromAddr = 0;
void incEepromAddr(){
	if(++eepromAddr >= 512){
		eepromAddr=0;
	}
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Pressure Sensor Test");
  Serial.println("");
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
	  Serial.println("There was a problem detecting the BMP085 ... check your connections");
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();

//	write_eeprom_word(&my_eeprom_array[0], 66);  // write value 1 to position 0 of the eeprom array
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
//	delay(7200);
	delay(512);
	static uint8_t sampleCnt=0;

  /* Get a new sensor event */
	sensors_event_t event;
  bmp.getEvent(&event);
  Serial.println(sampleCnt);
  if(sampleCnt%10==0) {
	  if(event.temperature){
		  float temperature;
		  bmp.getTemperature(&temperature);
		  uint16_t temp = (uint16_t)(temperature);
		  Serial.print("Temperature: ");
		  Serial.println(temp);
	  }
  } else {
	  if(event.pressure){
		  uint16_t press = (uint16_t)(event.pressure);
		  Serial.print("Pressure: ");
		  Serial.println(press);
	  }
  }
  sampleCnt++;
  return;

  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */

    /* Calculating altitude with reasonable accuracy requires pressure    *
     * sea level pressure for your position at the moment the data is     *
     * converted, as well as the ambient temperature in degress           *
     * celcius.  If you don't have these values, a 'generic' value of     *
     * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
     * in sensors.h), but this isn't ideal and will give variable         *
     * results from one day to the next.                                  *
     *                                                                    *
     * You can usually find the current SLP value by looking at weather   *
     * websites or from environmental information centers near any major  *
     * airport.                                                           *
     *                                                                    *
     * For example, for Paris, France you can check the current mean      *
     * pressure and sea level at: http://bit.ly/16Au8ol                   */

    /* First we get the current temperature from the BMP085 */
    float temperature;
    bmp.getTemperature(&temperature);

    uint16_t temp = (uint16_t)(temperature);
    Serial.print("Temperature: ");
    Serial.println(temp);
    delay(512);
    uint16_t press = (uint16_t)(event.pressure);
    Serial.print("Pressure: ");
    Serial.println(press);
    //eeprom_write_byte(&eeprom_byte_array[eepromAddr], (uint8_t)((uint32_t)temperature)<<2);
    //eeprom_write_byte(&eeprom_byte_array[eepromAddr], (uint8_t)((uint32_t)event.pressure)<<2);

    /* Then convert the atmospheric pressure, SLP and temp to altitude    */
    /* Update this next line with the current SLP for better results      */
#if 0
    float seaLevelPressure = 1012.0F;
    float altitude = bmp.pressureToAltitude(seaLevelPressure,
            event.pressure,
            temperature);
    static float avgAltitude = altitude;
    avgAltitude = altitude*0.5 + avgAltitude*0.5;

    //show on 7 segment LED
    for(uint32_t i=0;i<8;i++){
    	SevenSegment.printNum((int32_t)avgAltitude);
    }
#endif
  }
  else
  {
  }
}

