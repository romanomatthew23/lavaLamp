//Debug (uncomment the line below to enable serial monitor debugging
#define DEBUG 1

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Global Variables                           //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//Pin Values
const int heat = 11;   //PB2 (pin10) is the heat PWM output
const int button = A5;  //PD2 (pin2) is button input

//Other Global Variables
int buttonVal = 0;
int oldButtonVal = 0;
int lastSwitch = 0; //remember how many cycles ago we last switched our mode
int switchDelay = 5; //threshold to achieve before we can switch our mode again
int mode = 0;     //modes 0 thru 4


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
  pinMode(button, INPUT); //button input 
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                             Main Loop                                  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void loop()
{
  userInput();
  analogWrite(heat, mode);
  delay(10);
}



////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                   Read User Input (Button, Dimmer)                     //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void userInput()
{   
  
  #ifdef DEBUG
  Serial.print("PWM Val: ");
  Serial.print(mode);
  Serial.print("\n");
  #endif

  //read the button value
  oldButtonVal = buttonVal;
  buttonVal = digitalRead(button);
  if(lastSwitch > switchDelay)    //allow ourselves to switch
  {
     if(buttonVal && !oldButtonVal)  //sense rising edge
     {
       mode = ++mode % 256;            //toggle to the next mode
       lastSwitch = 0;
     }
  }
  else                            //don't switch yet, wait
  {
    lastSwitch++;
  }
}

