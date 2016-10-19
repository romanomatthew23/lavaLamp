//Pin Values
const int trimPot = A5; //PC5 (A5 pin19) is the trimpot input
const int heat = 10;   //PB2 (pin10) is the heat PWM output
const int led1 = 3;    //PD3 (pin3) is LED1
const int led2 = 5;    //PD5 (pin5) is LED2
const int led3 = 6;    //PD6 (pin6) is LED3
const int led4 = 9;    //PB1 (pin9) is LED4
const int button = 2;  //PD2 (pin2) is button input

//Other Global Variables
int redVal = 0;
int greenVal = 0;
int blueVal = 0;
int whiteVal = 0;
int heatVal = 0;
int buttonVal = 0;
int oldButtonVal = 0;
int mode = 0;     //modes 0 thru 4
void setup()
{
  Serial.begin(9600); //open a serial port
  
  pinMode(heat, OUTPUT);  //pwm outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(button, INPUT); //button input 
}

void loop()
{
  //analog read
  int potVal = analogRead(trimPot);
  Serial.print("Pot Value: ");
  Serial.print(potVal);
  Serial.print("   mode: ");
  Serial.print(mode);
  Serial.print("\n");
  float voltage = (potVal / 1024.0) * 5.0;
  
  oldButtonVal = buttonVal;
  buttonVal = digitalRead(button);

  if(buttonVal && !oldButtonVal)
  {
      mode = ++mode % 5;
  }
}
