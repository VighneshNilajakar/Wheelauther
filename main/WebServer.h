#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WebServer.h>
#include "ModeManager.h"

class WebServerManager {
private:
    static ESP8266WebServer server;
    static void handleRoot();
    static void handleModeSwitch();
    static void handleMotorControl();
    static void handleDeautherControl();
    
public:
    static void initialize();
    static void handle();
};

#endif