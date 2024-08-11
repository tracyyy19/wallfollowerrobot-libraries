//#include <util_delay.h>  // Include the AVR delay library
#include <motor.h>
#include <myultrasonic.h>

#define SERVO_PERIOD 20000  // Microseconds (20 milliseconds)

#define TRIGGER_PIN PB4 // PIN 12 trigger on sensor
#define ECHO_PIN PB5     // PIN 13 echo on sensor
#define SERVO_PIN 10

#define RIGHT_TARGET_DISTANCE 12 // Target distance from the right wall in inches
#define FRONT_CLEARANCE 20 // Minimum clearance needed in front in inches
#define ERROR_THRESHOLD 2  // Allowed error in inches

void setup() {
  setupUltra();
  setupMotorPins();
  pinMode(SERVO_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  double r = checkRightDistance();
  double f = checkFrontDistance();
  Serial.print("RIGHT: ");
  Serial.println(r);
  Serial.print("FRONT: ");
  Serial.println(f);

  if (r<5){ // too close at right
    turnMotor(LEFT, 70, SMALL_TURN_DURATION);
  }
  else if (r<6 && f<6){ // Too close to right and front
    moveMotor(BACKWARD, 100, 700);
  } else if(r<10 && f<10){ // target distance, corner detected
    //moveMotor(BACKWARD, 70, 700);
    turnMotor(LEFT, 180, SMALL_TURN_DURATION);
  } else if (r<10 && f>10){ // target right distance, no wall up ahead
    moveMotor(FORWARD, 100, MOVE_DURATION);
  } else if(r>10 && f>10) { // too far away
    turnMotor(RIGHT, 150, SMALL_TURN_DURATION);
    //moveMotor(BACKWARD, 70, 700);
    // turnMotor(LEFT, 70, SMALL_TURN_DURATION);
  } else{ // too far from right, too close to front (r>10 and f<10)
    moveMotor(BACKWARD, 70, 700);
    turnMotor(RIGHT, 70, SMALL_TURN_DURATION);
    moveMotor(FORWARD, 70, 700);
    turnMotor(LEFT, 100, SMALL_TURN_DURATION);
  }
  stopMotor();
  delay(100);  // Short delay to stabilize readings
}

double checkRightDistance() {
  setServoPosition(350);  // Point sensor to the right side
  delay(60);
  return checkDistance();
}

double checkFrontDistance() {
  setServoPosition(1400); // Point sensor forward
  delay(60);
  return checkDistance();
}