//some demo code
#include <ESP8266WiFi.h> //forlater

const int REEDPIN = D2;
bool reeddetected = false;
bool alarmon = false;
int alarmhours = 7;
int alarmminutes = 30;
int currhours = 0;
int currminutes = 0;

void setup() {
  Serial.begin(9600);
  pinMode(REEDPIN, INPUT_PULLUP);
}

void loop() {
  //Serial.println(digitalRead(REEDPIN));
  if(digitalRead(REEDPIN) == LOW){
    reeddetected = true;
  }
  else{
    reeddetected = false;
  }
  //update time here 
  alarm();
  if(alarmon && !reeddetected){
    //do annoying stuff;
  }
  else if(alarmon && reeddetected){
    //disablealarm
  }
}
void alarm(){
  if((currhours >= alarmhours) && (currminutes >= alarmminutes)){
    alarmon = true;
  }
}


