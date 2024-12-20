#include "ModeManager.h"
#include "MotorControl.h"
#include "DeautherControl.h"

OperatingMode ModeManager::currentMode = MOTOR_DRIVER;
bool ModeManager::isTransitioning = false;

OperatingMode ModeManager::getCurrentMode() {
    return currentMode;
}

bool ModeManager::switchMode(OperatingMode newMode) {
    if (isTransitioning || newMode == currentMode) return false;
    
    isTransitioning = true;
    
    // Cleanup current mode
    if (currentMode == MOTOR_DRIVER) {
        MotorControl::shutdown();
    } else {
        DeautherControl::shutdown();
    }
    
    // Initialize new mode
    if (newMode == MOTOR_DRIVER) {
        MotorControl::initialize();
    } else {
        DeautherControl::initialize();
    }
    
    currentMode = newMode;
    isTransitioning = false;
    return true;
} 