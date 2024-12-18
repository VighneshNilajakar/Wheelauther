#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <pins_arduino.h>

class MotorControl {
public:
    MotorControl();
    void begin();
    void update();
    
    // Motor control functions
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stop();
    
private:
    // Motor pins according to documentation
    static const uint8_t MOTOR_1 = 14;  // GPIO14 (D5)
    static const uint8_t MOTOR_2 = 12;  // GPIO12 (D6)
    
    // LED pin
    static const uint8_t STATUS_LED = LED_BUILTIN;  // GPIO2
    
    void setMotor1(bool active);
    void setMotor2(bool active);
    void updateStatusLED();
    
    bool isActive;
};

#endif // MOTOR_CONTROL_H 