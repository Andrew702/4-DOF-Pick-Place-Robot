#include <Servo_Hardware_PWM.h>

Servo myServo1; //creating a servo object (any custom name could be used)
unsigned int posreq = 0 , temp;
unsigned int currentpos = 0;
unsigned long previousMillis = 0;
unsigned long interval = 20;

void setup() {
	myServo1.attach(2); //attaches the servo to pin 2
}

void loop() {

  /*if (Serial.available())
  {
    temp = Serial.parseInt();
    if(temp)
      posreq = temp;
  }*/

 /* unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    if(currentpos < posreq)
    {
      currentpos++;
      myServo1.write(currentpos);
    }
    if(currentpos > posreq)
    {
      currentpos--;
      myServo1.write(currentpos);
    }
    previousMillis = currentMillis;
  }
  */
  for (currentpos = 195; currentpos > 110; currentpos--){ //goes from 180° to 0° (2500us to 500us)
  myServo1.write(currentpos);	//writes the value of valueDegrees to the servo
  delay(20);
	}

}
