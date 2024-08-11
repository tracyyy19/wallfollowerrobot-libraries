#include "motor.h"

void stopMotor() {
  Serial.println("STOP");
  OCR0A = 0;  // Set PWM duty cycle to 0 to stop motor A
  OCR0B = 0;  // Set PWM duty cycle to 0 to stop motor B
  _delay_ms(STOP_DURATION);
}

void moveMotor(int direction, int pwmSpeed, int duration) {
  if (direction == FORWARD) {
    Serial.println("FORWARD");
    PORTD |= (1 << MOTOR_A_DIR);  // Set MOTOR_A_DIR high
    PORTD &= ~(1 << MOTOR_B_DIR); // Set MOTOR_B_DIR low
  } else if (direction == BACKWARD) {
    Serial.println("BACKWARD");
    PORTD &= ~(1 << MOTOR_A_DIR); // Set MOTOR_A_DIR low
    PORTD |= (1 << MOTOR_B_DIR);  // Set MOTOR_B_DIR high
  }
  OCR0A = pwmSpeed;    // Set PWM duty cycle for motor A
  OCR0B = pwmSpeed;    // Set PWM duty cycle for motor B
  _delay_ms(duration);
}

void turnMotor(int direction, int pwmSpeed, int duration) {
  if (direction == LEFT) {
    Serial.println(duration == SMALL_TURN_DURATION ? "SMALL TURN LEFT" : "LARGE TURN LEFT");
    PORTD &= ~(1 << MOTOR_A_DIR); // Set MOTOR_A_DIR low (left motor backward)
    PORTD &= ~(1 << MOTOR_B_DIR); // Set MOTOR_B_DIR low (right motor forward)
  } else if (direction == RIGHT) {
    Serial.println(duration == SMALL_TURN_DURATION ? "SMALL TURN RIGHT" : "LARGE TURN RIGHT");
    PORTD |= (1 << MOTOR_A_DIR);  // Set MOTOR_A_DIR high (left motor forward)
    PORTD |= (1 << MOTOR_B_DIR);  // Set MOTOR_B_DIR high (right motor backward)
  }
  OCR0A = pwmSpeed;    // Set PWM duty cycle for motor A
  OCR0B = pwmSpeed;    // Set PWM duty cycle for motor B
  _delay_ms(duration);
}

void setupMotorPins(){
  // Set motor control pins as output
  DDRD |= (1 << MOTOR_A_DIR) | (1 << MOTOR_B_DIR) | (1 << MOTOR_A_PWM) | (1 << MOTOR_B_PWM); // Set motor control pins as outputs

  // Setup Timer 0 for PWM on PD5 (OC0B)
  TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01); // Fast PWM, clear OC0A/OC0B on compare match
  TCCR0B = (1 << CS01);  // Prescaler 8
}