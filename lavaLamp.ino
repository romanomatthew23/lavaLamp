////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Global Variables                           //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//Pin Values
const int trimPot = A5;//PC5 (A5 pin19) is the trimpot input
const int button = 2;  //PD2 (pin2) is button input
const int heat = 10;   //PB2 (pin10) is the heat PWM output
const int led1 = 3;    //PD3 (pin3) is LED1 (assume is R) TODO: Check these assumptions
const int led2 = 5;    //PD5 (pin5) is LED2 (assume is G)
const int led3 = 6;    //PD6 (pin6) is LED3 (assume is B)
const int led4 = 9;    //PB1 (pin9) is LED4 (assume is W)
const int tempHeat=23; //PC0 (pin23) is Heat Source Temp Sensor
const int tempLamp=24; //PC1 (pin24) is Lava Lamp Temp Sensor

//Controller Parameters TODO Set These!!
float desiredTemp = 60;   //Desired Lava Lamp Tempin degrees Celsius
float maxHeatTemp = 85;   //Highest Allowable Heat Source Temp
float K = 1;              //Proportional gain constant

//Other Global Variables
float potVal = 0;
int buttonVal = 0;
int oldButtonVal = 0;
int mode = 0;     //modes 0 thru 4
int redVal = 0;
int greenVal = 0;
int blueVal = 0;
int whiteVal = 0;
int heatVal = 0;
float heatTemp = 25;  //heat source temp in Celsius
float lampTemp = 25;  //lava lamp temp in Celsius

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Initialize MCU                             //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(heat, OUTPUT);  //heat pwm output
  pinMode(led1, OUTPUT);  //led pwm outputs
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(button, INPUT); //button input 
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Main Loop                                  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void loop()
{
  //Light
  userInput();  //Read User Input (Button, Dimmer)
  calcLEDs();   //Calculate LED PWM Signals
  setLEDs();    //set LED PWM Signals;
  
  //Heat
  tempInput();  //Read Temperature Sensors
  calcHeat();   //Calculate Heat PWM Signals
  setHeat();    //Set Heat PWM Signals
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                              Functions                                 //
//                                                                        //
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                   Read User Input (Button, Dimmer)                     //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void userInput()
{
  //read the dimmer value
  potVal = analogRead(trimPot) / 1024;

  //read the button value
  oldButtonVal = buttonVal;
  buttonVal = digitalRead(button);
  if(buttonVal && !oldButtonVal)  //sense rising edge
  {
    mode = ++mode % 5;            //toggle to the next mode
  }
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                    Calculate LED PWM Signals                           //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void calcLEDs()
{
  //obtain the color first
  switch(mode) {
      case '0' :  //red
         redVal = 255;
         greenVal = 0;
         blueVal = 0;
         whiteVal = 255;
         break;
      case '1' :  //green
         redVal = 0;
         greenVal = 255;
         blueVal = 0;
         whiteVal = 255;
      case '2' : //blue
         redVal = 0;
         greenVal = 0;
         blueVal = 255;
         whiteVal = 255;
         break;
      case '3' : //purple
         redVal = 255;
         greenVal = 0;
         blueVal = 255;
         whiteVal = 255;
         break;
      case '4' : //aqua
         redVal = 0;
         greenVal = 255;
         blueVal = 255;
         whiteVal = 255;
         break;
   }
   //next adjust the values to be the correct overall intensity
   //TODO: May have to incorporate magnitude into it to correct for certain colors
      //having too much light from having more channels, etc.
   //float magnitude = sqrt(sq(redVal)+sq(greenVal)+sq(blueVal)+sq(whiteVal));
   redVal = redVal*potVal;
   greenVal = greenVal*potVal;
   blueVal = blueVal*potVal;
   whiteVal = whiteVal*potVal;
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                        Set LED PWM Signals                             //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void setLEDs() 
{
  analogWrite(led1,redVal);
  analogWrite(led2,greenVal);
  analogWrite(led3,blueVal);
  analogWrite(led4,whiteVal);      
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                        Read Temperature Sensors                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void tempInput()  
{
  //read the Heat Source Temperature Sensor
  float voltage = analogRead(tempHeat) / 1024 * 5.0;
  heatTemp = (voltage - 0.5)*100;

  //read the Lava Lamp Temperature Sensor
  voltage = analogRead(tempLamp) / 1024 * 5.0;
  lampTemp = (voltage - 0.5)*100;
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                      Calculate Heat PWM Signals                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void calcHeat()   
{
  //check safety condition on heat source
  if(heatTemp > maxHeatTemp)
  {
    heatVal = 0;
    return;  
  }

  //Simple Proportional Controller
  float error = desiredTemp - lampTemp;
  int value = error * K;
  heatVal = value % 256;
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                        Set Heat PWM Signals                            //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void setHeat()   
{
  analogWrite(heat,heatVal);
}
