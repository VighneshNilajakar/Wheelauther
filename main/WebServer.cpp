#include "WebServer.h"

WebServer::WebServer() : server(80) {}

void WebServer::begin(MotorControl* mc) {
    motorControl = mc;
    setupRoutes();
    server.begin();
}

void WebServer::setupRoutes() {
    // Serve the main HTML page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>ESP Motor Control</title>
                <style>
                    body {
                        margin: 0;
                        padding: 0;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        min-height: 100vh;
                        background-color: #f0f0f0;
                        font-family: Arial, sans-serif;
                    }
                    .container {
                        display: flex;
                        flex-direction: column;
                        align-items: center;
                        gap: 20px;
                    }
                    .joystick-container {
                        width: 300px;
                        height: 300px;
                        background-color: #fff;
                        border-radius: 50%;
                        box-shadow: 0 4px 8px rgba(0,0,0,0.1);
                        position: relative;
                        touch-action: none;
                    }
                    #stick {
                        width: 100px;
                        height: 100px;
                        background-color: #2196F3;
                        border-radius: 50%;
                        position: absolute;
                        top: 50%;
                        left: 50%;
                        transform: translate(-50%, -50%);
                        cursor: pointer;
                    }
                    .status-panel {
                        background-color: #fff;
                        padding: 15px;
                        border-radius: 10px;
                        box-shadow: 0 2px 4px rgba(0,0,0,0.1);
                        text-align: center;
                    }
                </style>
            </head>
            <body>
                <div class="container">
                    <div class="joystick-container">
                        <div id="stick"></div>
                    </div>
                    <div class="status-panel">
                        <div id="connection-status">Connected</div>
                        <div id="direction-status">Stopped</div>
                    </div>
                </div>
                <script>
                    class Joystick {
                        constructor() {
                            this.stick = document.getElementById('stick');
                            this.container = document.querySelector('.joystick-container');
                            this.bounds = this.container.getBoundingClientRect();
                            this.centerX = this.bounds.width / 2;
                            this.centerY = this.bounds.height / 2;
                            this.active = false;
                            this.currentDirection = 'stop';
                            
                            this.setupEvents();
                        }

                        setupEvents() {
                            this.container.addEventListener('mousedown', (e) => this.handleStart(e));
                            document.addEventListener('mousemove', (e) => this.handleMove(e));
                            document.addEventListener('mouseup', () => this.handleEnd());

                            // Touch events
                            this.container.addEventListener('touchstart', (e) => {
                                e.preventDefault();
                                this.handleStart(e.touches[0]);
                            });
                            document.addEventListener('touchmove', (e) => {
                                e.preventDefault();
                                this.handleMove(e.touches[0]);
                            });
                            document.addEventListener('touchend', () => this.handleEnd());
                        }

                        handleStart(e) {
                            this.active = true;
                            this.move(e.clientX, e.clientY);
                        }

                        handleMove(e) {
                            if (this.active) {
                                this.move(e.clientX, e.clientY);
                            }
                        }

                        handleEnd() {
                            this.active = false;
                            this.stick.style.transform = 'translate(-50%, -50%)';
                            this.sendCommand('stop');
                        }

                        move(clientX, clientY) {
                            const bounds = this.container.getBoundingClientRect();
                            const x = clientX - bounds.left - this.centerX;
                            const y = clientY - bounds.top - this.centerY;
                            
                            const distance = Math.min(Math.sqrt(x*x + y*y), this.centerX);
                            const angle = Math.atan2(y, x);
                            
                            const moveX = Math.cos(angle) * distance;
                            const moveY = Math.sin(angle) * distance;
                            
                            this.stick.style.transform = `translate(calc(${moveX}px - 50%), calc(${moveY}px - 50%))`;
                            this.determineDirection(moveX, moveY);
                        }

                        determineDirection(x, y) {
                            const threshold = this.centerX / 3;
                            let direction = 'stop';

                            if (Math.abs(x) > Math.abs(y)) {
                                if (x > threshold) direction = 'right';
                                else if (x < -threshold) direction = 'left';
                            } else {
                                if (y > threshold) direction = 'backward';
                                else if (y < -threshold) direction = 'forward';
                            }

                            if (direction !== this.currentDirection) {
                                this.currentDirection = direction;
                                this.sendCommand(direction);
                            }
                        }

                        sendCommand(command) {
                            fetch(`/control?cmd=${command}`)
                                .then(response => {
                                    document.getElementById('direction-status').textContent = 
                                        command.charAt(0).toUpperCase() + command.slice(1);
                                })
                                .catch(error => {
                                    console.error('Error:', error);
                                    document.getElementById('connection-status').textContent = 'Disconnected';
                                });
                        }
                    }

                    // Initialize joystick when page loads
                    document.addEventListener('DOMContentLoaded', () => {
                        new Joystick();
                    });
                </script>
            </body>
            </html>
        )");
    });

    // Handle motor control commands
    server.on("/control", HTTP_GET, [this](AsyncWebServerRequest *request) {
        handleCommand(request);
    });
}

void WebServer::handleCommand(AsyncWebServerRequest *request) {
    String command = request->arg("cmd");
    
    if (command == "forward") {
        motorControl->moveForward();
    } else if (command == "backward") {
        motorControl->moveBackward();
    } else if (command == "left") {
        motorControl->turnLeft();
    } else if (command == "right") {
        motorControl->turnRight();
    } else if (command == "stop") {
        motorControl->stop();
    }
    
    request->send(200, "text/plain", "OK");
} 