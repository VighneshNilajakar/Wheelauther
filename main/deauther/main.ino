#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "MotorControl.h"
#include "WebServer.h"
#include "deauther/Attack.h"
#include "deauther/Scan.h"

enum OperatingMode {
    MODE_MOTOR,
    MODE_DEAUTHER
};

OperatingMode currentMode = MODE_MOTOR;
MotorControl motorControl;
WebServer webServer;
Attack deauthAttacker;
Scan wifiScanner;

void setup() {
    Serial.begin(115200);
    
    // Initialize both subsystems
    motorControl.begin();
    
    // Set up WiFi AP
    WiFi.softAP("ESP-Project", "12345678");
    
    // Initialize web server
    webServer.begin(&motorControl, &deauthAttacker, &wifiScanner);
}

void loop() {
    if(currentMode == MODE_MOTOR) {
        motorControl.update();
    } else {
        deauthAttacker.update();
        wifiScanner.update();
    }
    webServer.update();
}