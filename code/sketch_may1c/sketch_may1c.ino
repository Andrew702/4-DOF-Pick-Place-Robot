const int enPin=8;
const int stepXPin = 2; //X.STEP
const int dirXPin = 5; // X.DIR
const int stepYPin = 3; //Y.STEP
const int dirYPin = 6; // Y.DIR
const int stepZPin = 4; //Z.STEP
const int dirZPin = 7; // Z.DIR

 int stepPin=stepXPin;
 int dirPin=dirXPin;

const int stepsPerRev=200;
int pulseWidthMicros = 300;  // microseconds
int millisBtwnSteps = 3000;

void setup() {
  Serial.begin(9600);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

 
  Serial.println(F("CNC Shield Initialized"));
}

void loop() {
  digitalWrite(enPin, LOW);
  Serial.println(F("Running clockwise"));
  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  

  // Makes 200 pulses for making one full cycle rotation
  for (int i = 0; i < stepsPerRev; i++) {
    digitalWrite(stepPin, HIGH);

    delayMicroseconds(pulseWidthMicros);
    
    digitalWrite(stepPin, LOW);


    delayMicroseconds(millisBtwnSteps);
  }
  digitalWrite(enPin, HIGH);
  delay(3000);
}
