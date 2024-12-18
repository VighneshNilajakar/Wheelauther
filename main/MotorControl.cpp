#include "MotorControl.h"

MotorControl::MotorControl() : isActive(false) {}

void MotorControl::begin() {
    // Configure motor pins as outputs
    pinMode(MOTOR_1, OUTPUT);
    pinMode(MOTOR_2, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);
    
    // Initialize all motors to stopped state
    stop();
}

void MotorControl::update() {
    updateStatusLED();
}

void MotorControl::moveForward() {
    setMotor1(true);
    setMotor2(true);
    isActive = true;
}

void MotorControl::moveBackward() {
    setMotor1(false);
    setMotor2(false);
    isActive = true;
}

void MotorControl::turnLeft() {
    setMotor1(false);
    setMotor2(true);
    isActive = true;
}

void MotorControl::turnRight() {
    setMotor1(true);
    setMotor2(false);
    isActive = true;
}

void MotorControl::stop() {
    setMotor1(false);
    setMotor2(false);
    isActive = false;
}

void MotorControl::setMotor1(bool active) {
    digitalWrite(MOTOR_1, active);
}

void MotorControl::setMotor2(bool active) {
    digitalWrite(MOTOR_2, active);
}

void MotorControl::updateStatusLED() {
    digitalWrite(STATUS_LED, !isActive);  // LED is active LOW on ESP8266
} 