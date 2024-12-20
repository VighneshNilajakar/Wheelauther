#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

class MotorControl {
private:
    static const int MOTOR1_PIN = 14; // D5
    static const int MOTOR2_PIN = 12; // D6
    static bool isActive;
    
public:
    static void initialize();
    static void shutdown();
    static void update();
    static void setMotorSpeed(int motor, int speed);
    static bool isInitialized();
};

#endif 