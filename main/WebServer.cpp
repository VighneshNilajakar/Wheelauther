#include "WebServer.h"
#include <ArduinoJson.h>

ESP8266WebServer WebServerManager::server(80);

void WebServerManager::initialize() {
    server.on("/", HTTP_GET, handleRoot);
    server.on("/api/mode", HTTP_POST, handleModeSwitch);
    server.on("/api/motor", HTTP_POST, handleMotorControl);
    server.on("/api/deauther", HTTP_POST, handleDeautherControl);
    
    server.begin();
}

void WebServerManager::handleModeSwitch() {
    if (!server.hasArg("plain")) {
        server.send(400, "text/plain", "No data received");
        return;
    }
    
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, server.arg("plain"));
    
    if (error) {
        server.send(400, "text/plain", "Invalid JSON");
        return;
    }
    
    const char* mode = doc["mode"];
    OperatingMode newMode = strcmp(mode, "motor") == 0 ? MOTOR_DRIVER : DEAUTHER;
    
    if (ModeManager::switchMode(newMode)) {
        server.send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Mode switch failed\"}");
    }
}