#include "DeautherControl.h"
#include "ResourceManager.h"
#include "../deauther/Attack.h"
#include "../deauther/Scan.h"

bool DeautherControl::isActive = false;

void DeautherControl::initialize() {
    if (isActive) return;
    
    ResourceManager::initializeWiFi();
    // Initialize deauther components
    scan.init();
    attack.init();
    
    isActive = true;
}

void DeautherControl::shutdown() {
    if (!isActive) return;
    
    // Stop all active operations
    attack.stop();
    scan.stop();
    
    ResourceManager::cleanupWiFi();
    isActive = false;
}

void DeautherControl::update() {
    if (!isActive) return;
    
    scan.update();
    attack.update();
}

bool DeautherControl::startScan() {
    if (!isActive) return false;
    return scan.start();
}

bool DeautherControl::startAttack(int attackType) {
    if (!isActive) return false;
    return attack.start(attackType);
}