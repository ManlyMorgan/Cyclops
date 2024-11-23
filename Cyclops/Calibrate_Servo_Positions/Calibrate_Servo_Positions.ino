#include <Arduino.h>

#include "ServoEasing.hpp"

 
ServoEasing eyeLidServo;  // create servo object to control a servo
ServoEasing upDownServo;
ServoEasing leftRightServo;
// 16 servo objects can be created on the ESP32
 
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int eyeLidPin = 18;
int upDownPin = 17;
int leftRightPin = 16;

int eyeLidServoLower = 50;
int eyeLidServoUpper = 127;

int upDownServoLower = 30;
int upDownServoUpper = 120;

int leftRightServoLower = 50;
int leftRightServoUpper = 130;

void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	eyeLidServo.setPeriodHertz(50);    // standard 50 hz servos
  upDownServo.setPeriodHertz(50);    // standard 50 hz servo
  leftRightServo.setPeriodHertz(50);    // standard 50 hz servo

	// eyeLidServo.attach(eyeLidPin, 500, 1200); // attaches the servo on pin 18 to the servo object
  // upDownServo.attach(upDownPin, 500, 1200); // attaches the servo on pin 18 to the servo object
  // leftRightServo.attach(leftRightPin, 500, 1200); // attaches the servo on pin 18 to the servo object

  eyeLidServo.attach(eyeLidPin); // attaches the servo on pin 18 to the servo object
  upDownServo.attach(upDownPin); // attaches the servo on pin 18 to the servo object
  leftRightServo.attach(leftRightPin); // attaches the servo on pin 18 to the servo object
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep

  Serial.begin(115200);
  Serial.println("Enter servo positions in format x,y,z (0-180):");

  //home servos
  eyeLidServo.easeTo(100,40);
  upDownServo.easeTo(100,40);
  leftRightServo.easeTo(100,40);
  delay(500);
}
 
void loop() {
  // Check if data is available via Serial
  if (Serial.available() > 0) {
    // Read the input string
    String input = Serial.readStringUntil('\n');
    
    // Remove any leading or trailing whitespace
    input.trim();
    
    // Split the input string into three values (x, y, z)
    int index1 = input.indexOf(',');  // Find the first comma
    int index2 = input.indexOf(',', index1 + 1);  // Find the second comma

    if (index1 > 0 && index2 > index1) {
      // Parse each value as an integer
      int x = input.substring(0, index1).toInt();
      int y = input.substring(index1 + 1, index2).toInt();
      int z = input.substring(index2 + 1).toInt();
      
      // Ensure each value is within the valid range (0 to 180)
      if (x >= 0 && x <= 180 && y >= 0 && y <= 180 && z >= 0 && z <= 180) {
        // Move each servo to the corresponding position
        eyeLidServo.startEaseTo(x,40);
        upDownServo.startEaseTo(y,40);
        leftRightServo.startEaseTo(z,40);
        // Confirm the positions via Serial
        Serial.print("Servo positions set to: ");
        Serial.print("X = "); Serial.print(x);
        Serial.print(", Y = "); Serial.print(y);
        Serial.print(", Z = "); Serial.println(z);
      } else {
        Serial.println("Error: Values must be between 0 and 180.");
      }
    } else {
      Serial.println("Invalid input format. Use x,y,z (e.g., 90,45,120).");
    }
  }
}

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



