#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

// For delay times
#define MOVE_DURATION 1000  // Duration for forward/backward movement in milliseconds
#define SMALL_TURN_DURATION 300  // Duration for small turn in milliseconds
#define LARGE_TURN_DURATION 800  // Duration for large turn in milliseconds
#define STOP_DURATION 1000  // Duration for stopping the motor in milliseconds

// For motor control pins
#define MOTOR_A_DIR PD2
#define MOTOR_A_PWM PD5
#define MOTOR_B_DIR PD4
#define MOTOR_B_PWM PD6

// Define direction constants
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

void stopMotor();
void setupMotorPins();
void moveMotor(int direction, int pwmSpeed, int duration);
void turnMotor(int direction, int pwmSpeed, int duration);

#endif


