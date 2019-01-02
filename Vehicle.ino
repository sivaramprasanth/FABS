#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,2);
#include<LiquidCrystal.h>

//Declare the pins being used

//Pins for Right  motor
int RM1=A0;
int RM2=7;

//Pins for left motor
int LM1=A2;
int LM2=6;

int Y1 = A3;
int Y2 = A4;

int k =0;
String inp;
char A;
//Modes
/*
0 -  Normal
1 -  Special
00 - Learner 
01 - Traffic
10 - Highway
11 - Rain

*/
//int A5;

const int rs = 5, en = 4, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
 
//Steup the pin modes.
pinMode(RM1,OUTPUT);
pinMode(RM2,OUTPUT);
pinMode(LM1,OUTPUT);
pinMode(LM2,OUTPUT);
pinMode(A5, OUTPUT);
mySerial.begin(9600);
lcd.begin(16,2);
delay(0);
printScreen("FABS", 6, 0);
//delay(1000);
Serial.begin(9600);
}


void printScreen(String lol,int c1, int c2)
{

analogWrite(A5, 1023);
//lcd.begin(16,2);
lcd.clear();
lcd.setCursor(6, 0);
lcd.write("FABS"); 
lcd.setCursor(c1,c2);
lcd.print(lol);
analogWrite(A5, 0);
delay(100);
}

void loop() {
  //Get the data input for mode from other bluetooth.
        inp = "";
        
       while(mySerial.available()>0)
        {
          A = mySerial.read(); 
          if(A=='z')
          {
              Serial.end();
              Serial.begin(9600);            
              break;
            
          }
          inp.concat(A);   
        }
              
     //Split it into three parts

     //Our input would br of the following format.
     //First part would indicate the no. of bits represnting the speed followed by those many bits representing speed.The other bits represent the value of braking  
     Serial.println(inp);
     String mode =  inp.substring(0,3);

     int brk =  (inp.substring(3,5)).toInt()-10 ;

     int spd = (inp.substring(5,7)).toInt() -10;
//     inp = "";
//  Serial.println("#" + mode);
  if(mode.substring(0,1)=="0")
  {
    printScreen("NORMAL", 1, 1);
  }
  else if(mode.substring(0,1)=="1")
  {
    if(mode.substring(1, 3) == "00")  printScreen("LEARNER", 1, 1);
    else if(mode.substring(1, 3) == "01") printScreen("TRAFFIC", 1, 1);
    else if(mode.substring(1, 3) == "10") printScreen("HIGHWAY", 1, 1);
    else if(mode.substring(1, 3) == "11") printScreen("RAIN", 1, 1);
  }

  else  printScreen("DISCONNECTED", 1, 1);
  delay(0);
     
    if(spd>=0 && brk>=0)
    {
   
     if(spd-brk > 0)
     {
        spd = spd+200;
        brk = brk+50;   
         Serial.println(spd-brk);
         analogWrite(RM1,spd-brk);
         analogWrite(Y1,0);
         analogWrite(LM1,spd-brk);
         analogWrite(Y2,0);
         delay(0);  
     }


     else
     {
           spd = spd+50;
           brk = brk+200; 
           analogWrite(RM1,0);
           analogWrite(Y1,brk-spd);
           analogWrite(LM1,0);
           analogWrite(Y2,brk-spd);     
           
          // analogWrite(RM1,spd-brk);
          // digitalWrite(RM2,0);
          // analogWrite(LM1,spd-brk);
          // digitalWrite(LM2,0);     
     }
    }

 delay(0);
}
