#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;
/*
int second = 0;       
int minute = 0;   
int hour = 0;      
int day = 0;    
int month = 0;   
int year = 0; 
int dayOfWeek = 0;
*/
//boolean aflag = false; // a flag to see if led should be on


void setup () {
  Wire.begin();
  RTC.begin(); 
  Serial.begin(9600);
  Serial.print("\nThe current date and time will be updated every one seconds - set delay in code to change:\n\n");
}

void loop() {

  DateTime now = RTC.now();

  Serial.println();
  Serial.print(now.dayOfTheWeek(), DEC);
  Serial.print(" day of week\n"); 
  Serial.println();   
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println(); 
  delay(1000);
  Serial.println();
  Serial.print("Time = ");
  Serial.print(now.unixtime());


}
