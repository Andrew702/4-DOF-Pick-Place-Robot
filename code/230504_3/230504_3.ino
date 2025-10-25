#define Angle 0
#define Distance 1
#define CW 1
#define CCW 0

// PINS DEFINITIONS
const int enPin=8;
const int step1Pin = 2; //X.STEP
const int dir1Pin = 5; // X.DIR
const int step2Pin = 3; //Y.STEP
const int dir2Pin = 6; // Y.DIR
const int step3Pin = 4; //Z.STEP
const int dir3Pin = 7; // Z.DIR

int dirPin, stepPin;
unsigned int steps;


int pulseWidthMicros = 100; 
int microsBtwnSteps = 1000;


//Flags
bool stepperenabled = 0;

unsigned long previousTime[2] = {0}; // variable to store the previous time for each delay
unsigned long delayTime[2] = {100, 1000}; // delay times in microseconds
unsigned long currentTime;

bool checkMicroDelay(int index) {
  currentTime = micros(); // get the current time in microseconds
  if (currentTime - previousTime[index] >= delayTime[index]) { // check if the desired delay has elapsed
    previousTime[index] = currentTime; // update the previous time
    return true; // return true if the delay has elapsed
    }
  return false; // return false otherwise
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SteppersInitialize(); //function to initialize steppers as output pins
  SetStepperMove(1,Distance,8,CW);
}

void loop() {
  // put your main code here, to run repeatedly:
  StepperMove();
  Serial.println(stepperenabled);
}


void SteppersInitialize(void) //function to initialize steppers as output pins
{
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  pinMode(step1Pin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(step2Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
  pinMode(step3Pin, OUTPUT);
  pinMode(dir3Pin, OUTPUT);
}

void SetStepperMove(int StepperNo, bool operating_option, float position, bool direction)
{
  // position is specified in mm, angle is in degrees
  //if operating operation = 0 ---> angle
  //if operating operation = 1 ---> distance
  //if direction = 1 ---> clockwise/up/forward
  //if direction = 0 ---> anticlockwise/down/backward
  //---------------------------------------------------------------------------------------

  float angle;

  if(operating_option) // in mm
  {
    angle = (360*position)/4; // lead is 4mm
    steps = angle/1.8;
  }
  else
  {
    steps = position/1.8;
  }

  if(StepperNo == 1)
  {
    stepPin = step1Pin;
    dirPin = dir1Pin;
  }
  else if(StepperNo == 2)
  {
    stepPin = step2Pin;
    dirPin = dir2Pin;
  }
  else if(StepperNo == 3)
  {
    stepPin = step3Pin;
    dirPin = dir3Pin;
  }

  if(direction)
     digitalWrite(dirPin, HIGH);
  else
    digitalWrite(dirPin, LOW);

  stepperenabled = 1;
  
}

void StepperMove()
{ 
  {
    //start motion
    static int i  = 0;
    static bool flag = 0;

    if(i<steps)
    {
      if(!flag)
      {

        digitalWrite(stepPin, HIGH);
        if(checkMicroDelay(1))
        {
          digitalWrite(stepPin, LOW);
          flag = 1;
          previousTime[2] = currentTime;
        }
      }
      else if(flag)
      {
        if(checkMicroDelay(2))
        {
          flag = 0;
          previousTime[1] = currentTime;
          i++;
        }
      }
    }
    else
    {
      i = 0;
      stepperenabled = 0;
    }
  }
}

