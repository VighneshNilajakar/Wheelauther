#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "MotorControl.h"
#include "WebServer.h"

// WiFi credentials for Access Point
const char* ssid = "ESP Motor Control";
const char* password = "12345678";

// Global objects
MotorControl motorControl;
WebServer webServer;

void setup() {
    Serial.begin(115200);
    
    // Initialize motor control
    motorControl.begin();
    
    // Set up WiFi Access Point
    WiFi.softAP(ssid, password);
    
    Serial.println("\nAccess Point Started");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());  // Print AP IP address
    
    // Initialize web server
    webServer.begin(&motorControl);
}

void loop() {
    motorControl.update();  // Handle any motor updates
}
