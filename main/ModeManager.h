#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

enum OperatingMode {
    MOTOR_DRIVER,
    DEAUTHER
};

class ModeManager {
private:
    static OperatingMode currentMode;
    static bool isTransitioning;

public:
    static OperatingMode getCurrentMode();
    static bool switchMode(OperatingMode newMode);
    static void initialize();
    static bool isInTransition();
};

#endif 