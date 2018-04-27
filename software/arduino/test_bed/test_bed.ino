#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <time.h>

const int REEDPIN = D5;
const int NEOPIXELPIN = D3;
bool alarmdisabled = false;
int alarmhours = 23;
int alarmminutes = 18;
int currhours = 0;
int currminutes = 0;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
String ssid = "iPhone";
String password = "mark1234";
void setup() {
  Serial.begin(9600);
  pinMode(REEDPIN, INPUT_PULLUP);
  ring.begin();
  ring.clear();
  ring.show();

  WiFi.mode(WIFI_STA);
  WiFi.begin("iPhone", "mark1234");
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(1000);
  }
  configTime((-4) * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

bool timecompare(int a, int b, int c, int d){
  int temp1 = a*100;
  temp1 = temp1 + b;
  int temp2 = c*100;
  temp2 = temp2 + d;
  if(temp1 >= temp2){
    return true;
  }
  else{
    return false;
  }
}

void loop() {

  //update time here
    time_t now = time(nullptr);
    Serial.println(ctime(&now));
    
    int temp = 0;
    if(ctime(&now)[11] != 0){
      currhours = (ctime(&now)[11] - '0');
      currhours = currhours*10;
    }
    currhours = currhours + (ctime(&now)[12] - '0');
    //Serial.println(currhours);
    temp = 0;
    if(ctime(&now)[14] != 0){
      currminutes = (ctime(&now)[14] - '0');
      currminutes = currminutes*10;
    }
    currminutes = currminutes + (ctime(&now)[15] - '0');
    //Serial.println(currminutes);
    
    //Serial.println(hour(&now);
    delay(1000);
  
  while((timecompare(currhours, currminutes, alarmhours, alarmminutes)==true) && (alarmdisabled == false)){
    //play sound
    //light up neopixel
    ring.clear();
    int color[] = {255, 0 ,0};
    for(int i = 0; i < 16; i++){
      ring.setPixelColor(i, 255, 0, 0);
    }
    ring.show();
    Serial.println("ALARM");
    
    if(digitalRead(REEDPIN) == LOW){
      alarmdisabled = true;
    }
    
    delay(10);
  }
    ring.clear();
    for(int i = 0; i < 16; i++){
      ring.setPixelColor(i, 0,0,0);
    }
     ring.show();
  //Serial.println(digitalRead(REEDPIN));
}





