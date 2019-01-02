#include <SoftwareSerial.h>

SoftwareSerial mySerial(8,2);

//Declaring the variables
int brk[5] = {7, 6, 5, 4, 3}; //Ports for brake pedal
int spd[5] = {13, 12, 11, 10, 9}; //Ports for Speed pedal
int Modes[3] = {A3, A4, A5}; //Ports for mode
int spdI = 0;
int brkI = 0;
int idx = 0;

void setup() {
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

    spdI = 0;
    brkI = 0;
    idx = 0;
    //Converting digital data from pedals to analog.
    for(int i = 1; i <= 16; i = 2*i){
        spdI = spdI + i*digitalRead(spd[idx++]);
    }
    idx = 0;

    for(int i = 1; i <= 16; i = 2*i){
        brkI = brkI + i*digitalRead(brk[idx++]);
    }

    //Finding the mode Number
    int modeNo = 2*digitalRead(Modes[2]) + digitalRead(Modes[1]);
    int spdO, brkO;


    //Mapping the speed and brake to the corresponding mode
    if(digitalRead(Modes[0]) == 0) //If the mode is normal
    {
        spdO = spdI;
        brkO = brkI;
    }

    //If the mode is not normal
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

    // Converting data to a string to send to the vehicle
    String temp1 = String(spdO+10);
    String temp2 = String(brkO+10);
    Serial.println(temp1);
    Serial.println(temp2);
    String temp = String(digitalRead(Modes[0])) + String(digitalRead(Modes[1])) + String(digitalRead(Modes[2])) + temp2 + temp1 + 'z';

    //Sending the data through Bluetooth
    mySerial.print(temp);
    Serial.println(temp);
    delay(100);
}
