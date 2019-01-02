
/* Mode List:
 *0 -  Normal
 *1 -  Not Normal
 *00 - Learner
 *01 - Traffic
 *10 - Highway
 *11 - Rain
*/

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial mySerial(8,2);
//Declaring the variables for vehicle
int RM1=A0;
int RM2=7;

int LM1=A2;
int LM2=6;

int Y1 = A3;
int Y2 = A4;

int k = 0;
String inp;
char A;

//Declaring the variables for LCD
const int rs = 5, en = 4, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

    pinMode(RM1,OUTPUT);
    pinMode(RM2,OUTPUT);
    pinMode(LM1,OUTPUT);
    pinMode(LM2,OUTPUT);
    pinMode(A5, OUTPUT);
    mySerial.begin(9600);
    lcd.begin(16,2);
    delay(0);
    printScreen("FABS", 6, 0); // Prints 'FABS' on the display
    Serial.begin(9600);
}

//Function used to print data on the LCD.
void printScreen(String lol,int c1, int c2)
{
    analogWrite(A5, 1023);
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.write("FABS");
    lcd.setCursor(c1,c2);
    lcd.print(lol);
    analogWrite(A5, 0);
    delay(100);
}

void loop() {

    //Taking input from mySerial, Bluetooth Module
    //This data comes from the user end.

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

    Serial.println(inp);

    //Splitting the string to acquire the mode, speed and brake
    String mode =  inp.substring(0,3);
    int brk =  (inp.substring(3,5)).toInt()-10 ;
    int spd = (inp.substring(5,7)).toInt() -10;

    //Printing the current mode on the LCD
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

    //Running the motors with received speed and brake.
    if(spd>=0 && brk>=0)
    {

        if(spd-brk > 0)
        {
            spd = spd+210;
            brk = brk+50;
            analogWrite(RM1,spd-brk);
            analogWrite(Y1,0);
            analogWrite(LM1,spd-brk);
            analogWrite(Y2,0);
            delay(0);
        }


        else
        {
            analogWrite(RM1,0);
            analogWrite(Y1,0);
            analogWrite(LM1,0);
            analogWrite(Y2,0);
        }
    }
    delay(0);
}
