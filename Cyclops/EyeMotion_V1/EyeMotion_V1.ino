#include <Arduino.h>

#include "ServoEasing.hpp"


ServoEasing eyeLidServo;  // create servo object to control a servo
ServoEasing upDownServo;
ServoEasing leftRightServo;

// 16 servo objects can be created on the ESP32

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int eyeLidPin = 32;
int upDownPin = 33;
int leftRightPin = 25;


// Servo Limits
int eyeLidServoLower = 50;
int eyeLidServoUpper = 127;

int upDownServoLower = 30;
int upDownServoUpper = 120;
int upDownServoCentre = 75;

int leftRightServoLower = 50;
int leftRightServoUpper = 130;
int leftRightServoCentre = 90;

void setup() {
  Serial.begin(115200);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  eyeLidServo.setPeriodHertz(50);     // standard 50 hz servos
  upDownServo.setPeriodHertz(50);     // standard 50 hz servo
  leftRightServo.setPeriodHertz(50);  // standard 50 hz servo

  // eyeLidServo.attach(eyeLidPin, 500, 1200); // attaches the servo on pin 18 to the servo object
  // upDownServo.attach(upDownPin, 500, 1200); // attaches the servo on pin 18 to the servo object
  // leftRightServo.attach(leftRightPin, 500, 1200); // attaches the servo on pin 18 to the servo object

  eyeLidServo.attach(eyeLidPin);        // attaches the servo on pin 18 to the servo object
  upDownServo.attach(upDownPin);        // attaches the servo on pin 18 to the servo object
  leftRightServo.attach(leftRightPin);  // attaches the servo on pin 18 to the servo object
                                        // different servos may require different min/max settings
                                        // for an accurate 0 to 180 sweep

  //home servos
  eyeLidServo.setEaseTo(127);
  upDownServo.setEaseTo(upDownServoCentre);
  leftRightServo.easeTo(leftRightServoCentre);
  setEaseToForAllServosSynchronizeAndStartInterrupt(60);
  while (ServoEasing::areInterruptsActive()) {
    // Here you can insert your own code
    delay(10);
  }
  delay(250);
  eyeLidServo.easeTo(50,60);
  delay(100);

}


void loop() {
  eyeMotion();
}

void eyeMotion() {

  long currTime = millis();

  int eyeOpenShort = 300;  //quick blink time
  int eyeOpenMin = 600;
  int eyeOpenMax = 2000;
  int eyeOpenDuration = random(eyeOpenMin, eyeOpenMax);  //random time to keep eye open between blinks
  long lastBlinkTime = currTime + eyeOpenDuration; //do this first

  int eyeStillMin = 400;
  int eyeStillMax = 1200;
  int eyeStillDuration = random(eyeStillMin, eyeStillMax);  //random time to keep eye still before moving
  long lastMoveTime = currTime;

  // int nonSideEyeMin = 1000; //minimum time to not be in side eye, before potentially entering side eye
  // int nonSideEyeMax = 2000;
  // int nonSideEyeDuration = random(nonSideEyeMin,nonSideEyeMax);
  // long lastSideEyeTime = currTime;

  while (1) {  //until exit condition, prehaps a set ammount of time, randomly defined before calling the function

    currTime = millis();
    if ((currTime - lastBlinkTime) > eyeOpenDuration) {  //blink event
      blink(random(800, 1000), random(900, 1000), 0, 50);
      if (!random(0, 2)) {  //sometimes don't move eye when blinking
        moveEyeBall(random(400, 600), getRndEyePos(leftRightServoLower, leftRightServoUpper, leftRightServoCentre, 0.4), getRndEyePos(upDownServoLower, upDownServoUpper, upDownServoCentre, 0.4));
        lastMoveTime = millis();
      }
      if (!random(0, 5)) {                                           //1 in x chance
        eyeOpenDuration = random(eyeOpenShort, eyeOpenShort + 100);  //short blink (double)
      } else {
        eyeOpenDuration = random(eyeOpenMin, eyeOpenMax);  //next random duration for blinking
      }
      lastBlinkTime = millis();
    }

    currTime = millis();
    if ((currTime - lastMoveTime) > eyeStillDuration) {  //move eye event
      moveEyeBall(random(100, 200), getRndEyePos(leftRightServoLower, leftRightServoUpper, leftRightServoCentre, 1), getRndEyePos(upDownServoLower, upDownServoUpper, upDownServoCentre, 1));
      lastMoveTime = millis();
    }
  }
}

int getRndEyePos(float lowerLimit, float upperLimit, float centrePos, float centreFactor) {
  float upperRange = abs(upperLimit - centrePos);
  float lowerRange = abs(centrePos - lowerLimit);
  // int centreFactor = 0.25;

  // Serial.print("Lower Range for Random");
  // Serial.println(centrePos-(lowerRange*centreFactor));

  if (random(0, 3)) {  //x-1 in x chance
    // Serial.println("Normal");
    return random(centrePos - (lowerRange * centreFactor), centrePos + (upperRange * centreFactor));
  } else {  //1 in x chance
    // Serial.println("Rare");
    return random(lowerLimit, upperLimit);
  }
}

// Move eyeball to set position and set a single speed, both servos should finish moving at the same time for a realistic motion
void moveEyeBall(int speed, int posLR, int posUD) {

  // Serial.print("posLR: ");
  // Serial.print(posLR);
  // Serial.print(" posUD: ");
  // Serial.println(posUD);

  posLR = constrain(posLR, leftRightServoLower, leftRightServoUpper);
  posUD = constrain(posUD, upDownServoLower, upDownServoUpper);

  leftRightServo.setEaseTo(posLR);
  upDownServo.setEaseTo(posUD);
  setEaseToForAllServosSynchronizeAndStartInterrupt(speed);
}

void blink(int closeSpeed, int openSpeed, int closeDelay, int openPosition) {
  eyeLidServo.easeTo(eyeLidServoUpper, closeSpeed);
  delay(closeDelay);
  eyeLidServo.startEaseTo(openPosition, openSpeed);
}
