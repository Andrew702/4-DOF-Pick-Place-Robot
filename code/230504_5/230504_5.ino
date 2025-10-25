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
AccelStepper Stepper2(AccelStepper::DRIVER, step2Pin , dir2Pin);
AccelStepper Stepper3(AccelStepper::DRIVER, step3Pin , dir3Pin);

volatile int step_count = 0;


bool flag1 = 0;
int command=0;

void Stepper1Move(int position);


void setup() {

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  Stepper1.setMaxSpeed(1000);
  Stepper1.setAcceleration(500);
  Stepper1.setMaxSpeed(1000);
  Stepper1.setAcceleration(500);

  // set the initial position of the stepper motor
  Stepper1.setCurrentPosition(0);

  Serial.begin(9600);
 // Stepper1.moveTo(600);

}

void loop()
{

  if(Serial.available())
  {
    command = Serial.read();
  }

  if(command == '1')
    Stepper1Move(1000);
  else if(command == '2')
    Stepper1Move(0);

  if(!Stepper1.run())
  {
    digitalWrite(enPin, HIGH);
  }

}

void Stepper1Move(int position)
{
  digitalWrite(enPin, LOW);
  Stepper1.moveTo(position);
  command = 0;
}