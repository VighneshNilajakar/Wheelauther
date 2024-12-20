#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "config.h"
#include "MotorControl.h"
#include "WebServer.h"
#include "DeautherControl.h"
#include "ModeManager.h"

void setup() {
    Serial.begin(115200);
    
    // Initialize WiFi
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP8266_Project", "password123");
    
    // Initialize components
    ModeManager::initialize();
    WebServerManager::initialize();
    
    // Start in Motor Driver mode by default
    ModeManager::switchMode(MOTOR_DRIVER);
}

void loop() {
    WebServerManager::handle();
    
    // Handle current mode operations
    if (ModeManager::getCurrentMode() == MOTOR_DRIVER) {
        MotorControl::update();
    } else {
        DeautherControl::update();
    }
    
    yield(); // Allow ESP8266 to handle system tasks
}