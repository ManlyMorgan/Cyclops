#include <Arduino.h>

#include "ServoEasing.hpp"

ServoEasing myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// Possible PWM GPIO pins on the ESP32-S3: 0(used by on-board button),1-21,35-45,47,48(used by on-board LED)
// Possible PWM GPIO pins on the ESP32-C3: 0(used by on-board button),1-7,8(used by on-board LED),9-10,18-21
#define MICROSECONDS_FOR_ROTATING_SERVO_STOP 1500 // Change this value to your servos real stop value

void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
  if (myservo.attach(16, MICROSECONDS_FOR_ROTATING_SERVO_CLOCKWISE_MAX,
    MICROSECONDS_FOR_ROTATING_SERVO_COUNTER_CLOCKWISE_MAX, 100, -100) == INVALID_SERVO) {
        Serial.println(F("Error attaching servo"));
  }
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
  Serial.begin(115200);
  Serial.println("Enter servo pos:");
}

void loop() {
  

  if (Serial.available() > 0) {
    // Read the input string
    String input = Serial.readStringUntil('\n');
    Serial.println(input);
    // Remove any leading or trailing whitespace
    input.trim();
    int x = input.toInt();
    myservo.writeMicroseconds(x);
    // Serial.println("Enter servo positions in format x,y,z (0-180):");
  }

}

