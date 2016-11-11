//Debug (uncomment the line below to enable serial monitor debugging
#define DEBUG 1

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Global Variables                           //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//Pin Values
const int trimPot = A2;//PC5 (A5 pin19) is the trimpot input
const int button = A5;  //PD2 (pin2) is button input
const int heat = 11;   //PB2 (pin10) is the heat PWM output
const int ledG = 10;    //PD3 (pin3) is LED1 (assume is G) TODO: Check these assumptions
const int ledB = 3;    //PD5 (pin5) is LED2 (assume is B)
const int ledR = 4;    //PD6 (pin6) is LED3 (assume is R)
const int ledW = 9;    //PB1 (pin9) is LED4 (assume is W)
const int tempHeat=A0; //PC0 (pin23) is Heat Source Temp Sensor
const int tempLamp=A1; //PC1 (pin24) is Lava Lamp Temp Sensor

//Controller Parameters TODO Set These!!
float desiredTemp = 50;   //Desired Lava Lamp Tempin degrees Celsius
float maxHeatTemp = 70;   //Highest Allowable Heat Source Temp
float K = 10;              //Proportional gain constant
float maxInHeat = 100;    //100 W

//Other Global Variables
double potVal = 0;
int buttonVal = 0;
int oldButtonVal = 0;
int lastSwitch = 0; //remember how many cycles ago we last switched our mode
int switchDelay = 5; //threshold to achieve before we can switch our mode again
int mode = 0;     //modes 0 thru 4
int redVal = 0;
int greenVal = 0;
int blueVal = 0;
int whiteVal = 0;
int heatVal = 0;
float heatTempAvg = 25.0;  //heat source temp in Celsius. This is actually the average of the last 8 temps using arrays below
float lampTempAvg = 25.0;  //lava lamp temp in Celsius. This is actually the average of the last 8 temps using arrays below
float heatTemp[8] = {25.0,25.0,25.0,25.0,25.0,25.0,25.0,25.0};  //arrays for last 8 temps to average
float lampTemp[8] = {25.0,25.0,25.0,25.0,25.0,25.0,25.0,25.0};
int heatIndex = 0;                                              //indices for the arrays for easy access
int lampIndex = 0;

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

  //TODO Remove this! Only for testing
  //analogReference(EXTERNAL);
  
  pinMode(heat, OUTPUT);  //heat pwm output
  pinMode(ledG, OUTPUT);  //led pwm outputs
  pinMode(ledB, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledW, OUTPUT);
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
  //setHeat();    //Set Heat PWM Signals

  delay(10);
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
  potVal = analogRead(trimPot) / 1024.0;
  
  #ifdef DEBUG
  Serial.print("Pot Value: ");
  Serial.print(potVal);
  /*
  Serial.print("   mode: ");
  Serial.print(mode);
  Serial.print("   red: ");
  Serial.print(redVal);
  Serial.print("   blue: ");
  Serial.print(blueVal);
  Serial.print("   green: ");
  Serial.print(greenVal);
  Serial.print("   white: ");
  Serial.print(whiteVal);
  Serial.print("\n");
  */
  #endif

  //read the button value
  oldButtonVal = buttonVal;
  buttonVal = digitalRead(button);
  if(lastSwitch > switchDelay)    //allow ourselves to switch
  {
     if(buttonVal && !oldButtonVal)  //sense rising edge
     {
       mode = ++mode % 5;            //toggle to the next mode
       lastSwitch = 0;
     }
  }
  else                            //don't switch yet, wait
  {
    lastSwitch++;
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
      case 0:  //red
         #ifdef DEBUG
         Serial.print(" Red Mode  ");
         #endif
         redVal = 255;
         greenVal = 0;
         blueVal = 0;
         whiteVal = 0;
         break;
      case 1:  //green
         #ifdef DEBUG
         Serial.print(" Green Mode  ");
         #endif
         redVal = 0;
         greenVal = 255;
         blueVal = 0;
         whiteVal = 0;
         break;
      case 2: //blue
         #ifdef DEBUG
         Serial.print(" Blue Mode  ");
         #endif
         redVal = 0;
         greenVal = 0;
         blueVal = 255;
         whiteVal = 0;
         break;
      case 3: //purple
         #ifdef DEBUG
         Serial.print(" Purple Mode  ");
         #endif
         redVal = 255;
         greenVal = 0;
         blueVal = 255;
         whiteVal = 0;
         break;
      case 4: //aqua
         #ifdef DEBUG
         Serial.print(" Aqua Mode  ");
         #endif
         redVal = 0;
         greenVal = 255;
         blueVal = 255;
         whiteVal = 0;
         break;
      default:
         #ifdef DEBUG
         Serial.print(" Default Mode  ");
         #endif
         redVal = 0;
         greenVal = 0;
         blueVal = 0;
         whiteVal = 0;
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
  analogWrite(ledR,redVal);
  analogWrite(ledG,greenVal);
  analogWrite(ledB,blueVal);
  analogWrite(ledW,whiteVal);      
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                        Read Temperature Sensors                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void tempInput()  
{
  //read the Heat Source Temperature Sensor
  //int tempRead = analogRead(tempHeat);

  //FIX PROBLEMS HERE!!! 
  float voltageH = analogRead(tempHeat) / 1024.0 * 3.3;
  heatTemp[heatIndex] = (voltageH - 0.5)*100.0;
  heatIndex = (heatIndex + 1) % 8;
  heatTempAvg = avgHeatTemps();

  //read the Lava Lamp Temperature Sensor
  float voltageL = analogRead(tempLamp) / 1024.0 * 3.3;
  lampTemp[lampIndex] = (voltageL - 0.5)*100.0;
  lampIndex = (lampIndex + 1) % 8;
  lampTempAvg = avgLampTemps();

  #ifdef DEBUG
  Serial.print(" heatTemp: ");
  Serial.print(heatTempAvg);
  Serial.print(" lampTemp: ");
  Serial.print(lampTempAvg);
  Serial.print("  ");
  //Serial.print(" heat Voltage: ");
  //Serial.print(voltageH);
  //Serial.print(" lamp Voltage: ");
  //Serial.print(voltageL);
  //Serial.print("\n");
  #endif
}

//helper function to calculate avg heat temp
float avgHeatTemps()
{
  float output = 0;
  for(int i=0; i<8; i++)
  {
    output = output + heatTemp[i];
  }
  output = output / 8.0;
  return output;
}

//helper function to calculate avg lamp temp
float avgLampTemps()
{
  float output = 0;
  for(int i=0; i<8; i++)
  {
    output = output + lampTemp[i];
  }
  output = output / 8.0;
  return output;
}
////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                      Calculate Heat PWM Signals                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void calcHeat()   
{
  //check safety condition on heat source
  if(heatTempAvg > maxHeatTemp)
  {
    heatVal = 0;
    #ifdef DEBUG
    Serial.print("Heat PWM Val: ");
    Serial.print("0 (for safety condition!)");
    Serial.print("\n");
    #endif
    return;  
  }
  if(desiredTemp < lampTempAvg)
  {
    heatVal = 0;
    #ifdef DEBUG
    Serial.print("Heat PWM Val: ");
    Serial.print("0 (above desired temp!)");
    Serial.print("\n");
    #endif
    return;
  }

  //Simple Proportional Controller
  float error = desiredTemp - lampTempAvg;
  heatVal = min(error * K / maxInHeat * 64,64);   //TODO currently limited to 1/4 power. Set to full later
  //heatVal = min(error * K,255);

  #ifdef DEBUG
  Serial.print("Heat PWM Val: ");
  Serial.print(heatVal);
  Serial.print("\n");
  #endif
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
