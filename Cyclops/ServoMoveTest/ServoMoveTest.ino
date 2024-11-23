#include <ESP32Servo.h>
 
Servo eyeLidServo;  // create servo object to control a servo
Servo upDownServo;
Servo leftRightServo;
// 16 servo objects can be created on the ESP32
 
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int eyeLidPin = 18;
int upDownPin = 17;
int leftRightPin = 16;

int eyeLidServoLower = 45;
int eyeLidServoUpper = 135;

int upDownServoLower = 5   ;
int upDownServoUpper = 135;

int leftRightServoLower = 90;
int leftRightServoUpper = 90;

void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	eyeLidServo.setPeriodHertz(50);    // standard 50 hz servo
  upDownServo.setPeriodHertz(50);    // standard 50 hz servo
  leftRightServo.setPeriodHertz(50);    // standard 50 hz servo

	eyeLidServo.attach(eyeLidPin, 500, 1200); // attaches the servo on pin 18 to the servo object
  upDownServo.attach(upDownPin, 500, 1200); // attaches the servo on pin 18 to the servo object
  leftRightServo.attach(leftRightPin, 500, 1200); // attaches the servo on pin 18 to the servo object
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep

  Serial.begin(115200);


  eyeLidServo.write((eyeLidServoLower+eyeLidServoUpper)/2);
  upDownServo.write((upDownServoLower+upDownServoUpper)/2);
  leftRightServo.write((leftRightServoLower+leftRightServoUpper)/2);
  delay(500);
}
 
void loop() {

  // sweepEyelid(eyeLidServoLower,eyeLidServoUpper);
  sweepUpDown(upDownServoLower,upDownServoUpper);
  delay(5);


//   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
// 		// in steps of 1 degree
// 		eyeLidServo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(15);             // waits 15ms for the servo to reach the position
// 	}
//   Serial.println("Min");
// 	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
// 		eyeLidServo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(15);             // waits 15ms for the servo to reach the position
// 	}
//   Serial.println("Min");
// }

}


void sweepEyelid(int lower, int upper){

	for (int pos = lower; pos <= upper; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		eyeLidServo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(10);             // waits 15ms for the servo to reach the position
	}
	for (int pos = upper; pos >= lower; pos -= 1) { // goes from 180 degrees to 0 degrees
		eyeLidServo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(10);             // waits 15ms for the servo to reach the position
	}

}

void sweepUpDown(int lower, int upper){

	for (int pos = lower; pos <= upper; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		upDownServo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(10);             // waits 15ms for the servo to reach the position
	}
	for (int pos = upper; pos >= lower; pos -= 1) { // goes from 180 degrees to 0 degrees
		upDownServo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(10);             // waits 15ms for the servo to reach the position
	}

}
