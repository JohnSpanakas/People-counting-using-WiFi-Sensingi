
#include <RTClib.h>
#include "ArduinoJson.h"
#include <Wire.h>

#define out_sensor 5
#define in_sensor 4
#define redButton 3
#define greenButton 2

//Δημιουργία αντικειμένου RTC μέσω της κλάσης RTC_DS1307
RTC_DS1307 RTC;

// Δημιουργία στατικού χώρου στη μνήμη για αποθήκευση του json αρχείου μεγέθους 96 Bytes
StaticJsonDocument <96> doc;

int out_state=digitalRead(out_sensor);
int in_state=digitalRead(in_sensor);
int cnt = 0;
int gB, rB;

void setup() {
  //put your setup code here, to run once:
  pinMode(out_sensor, INPUT);
  pinMode(in_sensor, INPUT);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  Serial.begin(9600);
  Wire.begin();
  RTC.begin(); 

  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  } 
}

void loop() {
  
  while(digitalRead(in_sensor) || digitalRead(out_sensor)){
     // ENTRY STATE RECOGNITION
    if (digitalRead(out_sensor) && !digitalRead(in_sensor)){
      while(!digitalRead(in_sensor) && digitalRead(out_sensor)){
        // wait
        delay(50);
      }
      
     if (digitalRead(in_sensor) && digitalRead(out_sensor)){
        
          cnt = cnt +1;
          DateTime now = RTC.now();
          uint32_t unix =now.unixtime();
          doc["Time"] = unix;
          doc["State"] ="Entry";
          doc["Number of People"] = cnt;
          serializeJson(doc, Serial);
          Serial.println();
          deserializeJson(doc, Serial);

      }
      while(digitalRead(in_sensor) || digitalRead(out_sensor)){
        delay(50);
      }
    }
    // EXIT STATE RECOGNITION
    else if (!digitalRead(out_sensor) && digitalRead(in_sensor)){
      while(digitalRead(in_sensor) && !digitalRead(out_sensor)){
        // wait
        delay(50);
      }
      if (digitalRead(in_sensor) && digitalRead(out_sensor)){
        cnt = cnt -1;
        DateTime now = RTC.now();
        uint32_t unix =now.unixtime();
        doc["Time"] = unix;
        doc["State"] ="Exit";
        doc["Number of People"] = cnt;
        serializeJson(doc, Serial);
        Serial.println();
        deserializeJson(doc, Serial);
      }
      while(digitalRead(in_sensor) || digitalRead(out_sensor)){
       delay(50);
      }
    }
  }

  gB=digitalRead(greenButton);
  delayMicroseconds(1);
  rB=digitalRead(redButton);
  delayMicroseconds(1);

  // WHEN GREEN BUTTON IS PUSHED
  if (!gB){
    
    cnt = cnt + 1;
    DateTime now = RTC.now();
    uint32_t unix =now.unixtime();
    doc["Time"] = unix;
    doc["Number of People"] = cnt;
    serializeJson(doc, Serial);
    Serial.println();
    deserializeJson(doc, Serial);
  }
  // WHEN RED BUTTON IS PUSHED
  else if (!rB){
    
    cnt = cnt - 1;
    DateTime now = RTC.now();
    uint32_t unix =now.unixtime();
    doc["Time"] = unix;
    doc["Number of People"] = cnt;
    serializeJson(doc, Serial);
    Serial.println();
    deserializeJson(doc, Serial);
    
  }
 
  deserializeJson(doc, Serial);
 //delay(500);

}
