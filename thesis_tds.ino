  #include <EEPROM.h>
#include "GravityTDS.h"
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define TdsSensorPin A3
GravityTDS gravityTds;
 
float tdsValue = 0;
 
void setup()
{
    Serial.begin(9600);
    lcd.begin();
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC

    // Calibration
    float calibrationFactor = 0.8; // adjust this value to calibrate the readings
    gravityTds.setKvalue(calibrationFactor * 0.5); // set K-value using the calibration factor
  
    gravityTds.begin();  //initialization
}
 
void loop()
{
   
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue(); // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    lcd.setCursor(0, 0);
    lcd.print("SALINITY METER:");
    lcd.setCursor(0, 1);
    lcd.print(tdsValue,0);
    lcd.print(" PPM");
    delay(1000);
    lcd.clear();
}
