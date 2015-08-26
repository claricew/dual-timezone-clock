#include "Wire.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define DS1307_I2C_ADDRESS 0x68
#define I2C_ADDR 0x3F // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
//pin locations for I2C
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}

void getDateDs1307(byte *second,byte *minute,byte *hour)
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
}

void setup()
{
  byte second, minute, hour;
  Wire.begin();
  lcd.begin(20, 4);
}

void loop()
{
  byte second, minute, hour, seoulhour;
  String s, m, h, sh;
  getDateDs1307(&second, &minute, &hour); //read in user input
  // ensure two digit spacing

  if (second < 10) { s = "0" + String(second); } else { s = String(second); }
  if (minute < 10) { m = "0" + String(minute); } else { m = String(minute); }
  if (hour < 10) { h = " " + String(hour); } else { h = String(hour); }
  // time conversion
  
  if (hour + 16 < 24) {
    seoulhour = hour + 16;
    if (seoulhour < 10) { sh = " " + String(seoulhour) }
    else { sh = String(seoulhour) }
  }
  else {
    seoulhour = (hour + 16) - 24;
    if (seoulhour < 10) { sh = " " + String(seoulhour) }
    else { sh = String(seoulhour) }
  }
  
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home (); // go home
  
  lcd.print("Seoul: " + sh + ":" + m + ":" + s + " ");
  lcd.setCursor ( 0, 1 ); // go to the 2nd line
  lcd.print(" SF: " + h + ":" + m + ":" + s + " ");
  lcd.setCursor ( 0, 2 ); // go to the third line
  
  delay(1000); //wait 1 second
}
