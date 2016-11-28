//Debug (uncomment the line below to enable serial monitor debugging
#define DEBUG 1

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Global Variables                           //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//Pin Values
const int ledG = 10;    //PD3 (pin3) is LED1 (assume is G) TODO: Check these assumptions
const int ledB = 3;    //PD5 (pin5) is LED2 (assume is B)
const int ledR = 5;    //PD6 (pin11) is LED3 (assume is R)
const int ledW = 9;    //PB1 (pin9) is LED4 (assume is W)

//Other Global Variables
int redVal = 0;
int greenVal = 0;
int blueVal = 0;
int whiteVal = 0;
int heatVal = 0;

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Initialize MCU                             //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  pinMode(ledG, OUTPUT);  //led pwm outputs
  pinMode(ledB, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledW, OUTPUT);
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Main Loop                                  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void loop()
{
  for(int i=0; i<256; i++)
  {
    analogWrite(ledR,i);
    analogWrite(ledG,i);
    analogWrite(ledB,i);
    analogWrite(ledW,i);
    delay(1000);
  }
}




