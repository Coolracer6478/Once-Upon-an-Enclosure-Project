#include <Servo.h>


// SERVO
Servo servo1;   // Scene 1 - Smokey (180°)
Servo servo2;   // Scene 2 - Throwing objects (360°)
Servo servo3;   // Scene 3 - Cow oscillating (360°)
Servo servo4;   // Scene 4 - Lightning push (180°)
Servo servo6;   // Scene 6 - Cruz donuts (360°)


// INPUT PINS (Copper wires)
int cw1 = 7;   // Scene 1
int cw2 = 8;   // Scene 2
int cw3 = 9;   // Scene 3
int cw4 = 10;   // Scene 4
int cw6b = 12;  // Scene 6 (Cruz donut servo)


// OUTPUT PINS 
int piezoPin = 13;           // Scene 5 piezo
int trigPin = 0;           // Scene 5 ultrasonic TRIG
int echoPin = 1;           // Scene 5 ultrasonic ECHO


// SERVO PINS
int servo1Pin = 2;
int servo2Pin = 3;
int servo3Pin = 4;
int servo4Pin = 5;
int servo6Pin = 6;


// STATE
bool servo4Moved = false;  // Scene 4 moves only once


void setup() {


  // Attach Servos
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo6.attach(servo6Pin);


  // Input Copper Wires
  pinMode(cw1, INPUT_PULLUP);
  pinMode(cw2, INPUT_PULLUP);
  pinMode(cw3, INPUT_PULLUP);
  pinMode(cw4, INPUT_PULLUP);
  pinMode(cw6b                                                                                                                                                                                                                                                                , INPUT_PULLUP);


  // Outputs
  pinMode(piezoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


// DISTANCE SENSOR 
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}


// MAIN LOOP 
void loop() {


  // Scene 1: Smokey turns 180 and stays 
  if (digitalRead(cw1) == HIGH) {
    servo1.write(360);
  }


  // Scene 2: 360 servo spins while triggered
  if (digitalRead(cw2) == HIGH) {
    servo2.write(180);  // spin
  } else {
    servo2.write(90);   // stop continuous servo
  }


  // Scene 3: Cow oscillating servo
  if (digitalRead(cw3) == HIGH) {
    servo3.write(0);
    delay(300);
    servo3.write(180);
    delay(300);
  }


  // Scene 4: Lightning push (180°, once)
  if (digitalRead(cw4) == HIGH && !servo4Moved) {
    servo4.write(180);
    servo4Moved = true;   // lock it so it never moves again
  }


  // Scene 5: Mac ultrasonic honk
  int distance = getDistance();
  if (distance < 1) {   // adjust threshold
    tone(piezoPin, 800); // honk (boom boom)
    delay(300);
    noTone(piezoPin);
    Serial.println ("ON");
  }

  // Scene 6: Cruz donuts
  if (digitalRead(cw6b) == HIGH) {
    servo6.write(180);  // spin
  } else {
    servo6.write(90);   // stop
  }
}



