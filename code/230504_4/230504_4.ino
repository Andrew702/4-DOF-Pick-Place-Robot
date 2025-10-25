#include <AccelStepper.h>
#include <MultiStepper.h>


const int enPin=8;
const int step1Pin = 2; 
const int dir1Pin = 5; 
const int step2Pin = 3;
const int dir2Pin = 6; 
const int step3Pin = 4;
const int dir3Pin = 7;

const int steps_per_revolution = 200;

AccelStepper Stepper1(AccelStepper::DRIVER, step1Pin , dir1Pin);

volatile int step_count = 0;


bool flag1 = 0;

void setup() {
  //SteppersInitialize();

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  Stepper1.setMaxSpeed(1000);
  Stepper1.setAcceleration(500);

  // set the initial position of the stepper motor
  Stepper1.setCurrentPosition(0);

  Serial.begin(9600);
 // Stepper1.moveTo(600);
  Stepper1Move(1000);

}

void loop()
{

  /*  if(!flag1 && Serial.available())
  {
    int position = Serial.parseInt();
        Stepper1.moveTo(position);
        flag1 = 1;

  }
  if(flag1)
  {
    Stepper1.run();
    if(Stepper1.distanceToGo() == 0)
      flag1=0;
  }
  */
  

  if(!Stepper1.run())
  {
      digitalWrite(enPin, HIGH);
  }
}

void Stepper1Move(int position)
{
  digitalWrite(enPin, LOW);
  Stepper1.moveTo(position);
}