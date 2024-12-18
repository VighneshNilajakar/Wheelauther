#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncWebServer.h>
#include "MotorControl.h"

class WebServer {
public:
    WebServer();
    void begin(MotorControl* motorControl);
    
private:
    AsyncWebServer server;
    MotorControl* motorControl;
    
    void setupRoutes();
    void handleCommand(AsyncWebServerRequest* request);
};

#endif // WEB_SERVER_H 