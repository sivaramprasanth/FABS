#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,2);
int brk[5] = {7,6,5,4,3};
int spd[5] = {13, 12, 11, 10, 9};
int Modes[3] = {A3, A4, A5};
 int spdI = 0;
 int brkI = 0;
 int idx = 0;
void setup() {
 // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  for(int i = 0; i < 5; i++){
    pinMode(spd[i], INPUT);
    pinMode(brk[i], INPUT);
  }
  for(int i = 0; i < 3; i++){
    pinMode(Modes[i], INPUT);
  }
}

void loop() {
// put your main code here, to run repeatedly:
 spdI = 0;
 brkI = 0;
 idx = 0;

 for(int i = 1; i <= 16; i = 2*i){
  spdI = spdI + i*digitalRead(spd[idx++]); 
 }

 idx = 0;
 for(int i = 1; i <= 16; i = 2*i){
  brkI = brkI + i*digitalRead(brk[idx++]); 
 }
 
 int modeNo = 2*digitalRead(Modes[2]) + digitalRead(Modes[1]);
 Serial.println("**" + modeNo);
 int spdO, brkO;
 
 if(digitalRead(Modes[0]) == 0)
 {
  spdO = spdI;
  brkO = brkI;
 }
 else
 {
  if(modeNo == 0)   //Learner mode
  {
    if(spdI < 25) spdO = spdI;
    else  spdO = 25;

    if(brkI < 25) brkO = 2*brkI;
    else brkO = 50;
  }
  else if(modeNo == 1) //Traffic mode
  {
    spdO = spdI/2;
    if(brkI < 30) brkO = 2*brkI;
    else brkO = 60;
  }

  else if(modeNo == 2)  //Highway mode
  {
    if(spdI < 40 && spdI > 0) spdO = spdI + 20;
    else if(spdI!=0) spdO = 40;
    else spdO=0;
  }

  else    //Rain mode
  {
    brkO = brkI/2;
    if(spdI < 30) spdO = spdI;
    else  spdO = 30;
  }
  
 }

  String temp1 = String(spdO+10);
  String temp2 = String(brkO+10);
  Serial.println(temp1);
  Serial.println(temp2);  
  String temp = String(digitalRead(Modes[0])) + String(digitalRead(Modes[1])) + String(digitalRead(Modes[2])) + temp2 + temp1 + 'z';
  mySerial.print(temp);
  Serial.println(temp);
  delay(100);
}
