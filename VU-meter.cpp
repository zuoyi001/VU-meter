#include <Wire.h> 
#include <OLED_I2C.h>           // http://rcl-radio.ru/wp-content/uploads/2022/01/OLED_I2C.zip

#define GAIN      100
#define STEP      3
#define LOW_SOUND 100
#define MAX_SOUND 600

  OLED  myOLED(SDA, SCL, 8);
  extern uint8_t SmallFont[];
  int strela=-45;
  int hMeter = 65;                      
  int vMeter = 85;                      
  int rMeter = 80;
  int ur,urr;
  unsigned long times;
  

void setup() {
  Serial.begin(9600);
  Wire.begin();Wire.setClock(400000L);
  myOLED.begin();
  myOLED.setBrightness(100);
  //  myOLED.invert(true);// invert
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  analogReference(INTERNAL);  // если очень маленький уровень сигнала
  pinMode(A0,INPUT);
}

void loop() {
 // times=millis(); 
  strela = map(log(analogRead(A0))*GAIN, LOW_SOUND,MAX_SOUND, -45,45);
  strela = constrain(strela, -45, 45);
  urr = strela;if(urr<ur){ur=ur-STEP;}else{ur = strela;}  
   
/////// PRINT //////////////////////////////////////////////////////////////// 
  myOLED.clrScr();
  myOLED.drawLine(10, 20, 85, 20);// line 1
  myOLED.drawLine(88, 20, 125, 20);myOLED.drawLine(88, 19, 125, 19);// line 2
  myOLED.drawLine(3, 23, 85, 23);// line3

  byte b1_2[10]{95,108,124,10,33,60,84,50,68,77};
  byte c1_2[10]{15,17,15,15,15,15,15,17,18,18};
  for(int i=0;i<10;i++){myOLED.drawLine(b1_2[i], 20, b1_2[i], c1_2[i]);} 
  byte b3[5]{3,25,48,67,84};
  for(int i=0;i<5;i++){myOLED.drawLine(b3[i], 23, b3[i], 27);}

  myOLED.print(F("20  10   3   0 1"), 3, 5);
  myOLED.print(F("0  25"), 0, 30);
  myOLED.print(F("50"), 42, 30);
  myOLED.print(F("75"), 61, 30);
  myOLED.print(F("100"), 75, 30);
  myOLED.print(F("2"), 106, 5);
  myOLED.print(F("3"), 120, 5);
  myOLED.print(F("-"), 3, 50);myOLED.print(F("+"), 119, 50);
  myOLED.print(F("VU meter"), CENTER, 50);
 
  int a1 = (hMeter + (sin(ur / 57.296) * rMeter)); // meter needle horizontal coordinate
  int a2 = (vMeter - (cos(ur / 57.296) * rMeter)); // meter needle vertical coordinate
  myOLED.drawLine(a1, a2, hMeter, vMeter);  
  myOLED.update();
 // Serial.println(millis()-times);
//////// END PRINT /////////////////////////////////////////////////////////
}
