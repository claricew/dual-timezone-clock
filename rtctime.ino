#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68
byte decToBcd(byte val)
{
return ( (val/10*16) + (val%10) );
}
void setDateDs1307(
byte second, //0-59
byte minute, //0-59
byte hour //1 - 23 in PST
)
{
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(0);
Wire.write(decToBcd(second));
Wire.write(decToBcd(minute));
Wire.write(decToBcd(hour));
Wire.endTransmission();
}
void setup()
{
byte second, minute, hour;
Wire.begin();
pinMode(13, OUTPUT);
//manual reset below:
// It is best to add 30 seconds to a minute to allow time for your computer to compile and upload the current time.
// Only run this script once, as running it again will overwrite the time set in the RTC chip!
// Hours are in 24 hour format
second = 0;
minute = 49;
hour = 19;
setDateDs1307(second, minute, hour);
//
}
void loop()
{
digitalWrite(13, HIGH); //turn the LED on (HIGH is the voltage level)
delay(1000); //wait for a second
digitalWrite(13, LOW); //turn the LED off by making the voltage LOW
delay(1000);
}
