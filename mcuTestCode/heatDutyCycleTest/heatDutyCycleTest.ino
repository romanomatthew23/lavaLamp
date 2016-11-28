//Debug (uncomment the line below to enable serial monitor debugging
#define DEBUG 1

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Global Variables                           //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//Pin Values
const int heat = 11;   //PB2 (pin10) is the heat PWM output


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

  pinMode(heat, OUTPUT);  //heat pwm output
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Main Loop                                  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void loop()
{
  for(int i=0; i<256; i++) {
    analogWrite(heat,i);
    delay(1000);
  }
}

