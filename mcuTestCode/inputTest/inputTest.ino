//Pin Values
const int trimPot = A2; //trimpot input
const int button = A5;  //button input

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
