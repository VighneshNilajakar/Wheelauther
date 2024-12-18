# Integration Instructions: ESP8266 Motor Driver and Deauther

## **Project Overview**

This document provides a detailed guide to integrate the **Motor Driver Code** with the **ESP8266 Deauther Code** into a single unified system. The integration enables the ESP8266 to perform both motor control and network testing (scanning and attacks) functionalities with a shared web interface for toggling between modes. The focus is on modularity, scalability, and efficient resource management.

---

## **Integration Goals**

1. Incorporate the Deauther’s core functionalities (scanning, deauthentication, beacon, and probe attacks) into the existing Motor Driver Code.
2. Ensure seamless toggling between Motor Driver and Deauther modes.
3. Maintain modularity by keeping motor control and Deauther logic in separate files.
4. Consolidate the web interface for mode selection and control.

---

## **Feature Requirements**

### **Motor Driver Features**
- Directional control of two DC motors (forward, backward, left, right, stop).
- Joystick-based web interface for motor control.
- Onboard LED feedback for motor states.

### **Deauther Features**
- Wi-Fi scanning for networks and connected devices.
- Deauthentication, beacon, and probe attacks.
- Real-time feedback through a web interface.

### **Shared Features**
- A unified web interface to toggle between Motor Driver and Deauther functionalities.
- Shared Wi-Fi AP setup for hosting the web server.
- Proper resource management to prevent conflicts between functionalities.

---

## **Current File Structure**

ESP MOTOR DRIVER:.
+---data
|       joystick.html
|       styles.css
|
+---esp8266_deauther
|   |   .gitignore
|   |   arduino-cli.yaml
|   |   README.md
|   |   serialcommands.md
|   |   settings.md
|   |
|   +---esp8266_deauther
|   |   |   Accesspoints.cpp
|   |   |   Accesspoints.h
|   |   |   Attack.cpp
|   |   |   Attack.h
|   |   |   A_config.h
|   |   |   CLI.cpp
|   |   |   CLI.h
|   |   |   debug.h
|   |   |   DisplayUI.cpp
|   |   |   DisplayUI.h
|   |   |   EEPROMHelper.h
|   |   |   esp8266_deauther.ino
|   |   |   functions.h
|   |   |   language.h
|   |   |   led.cpp
|   |   |   led.h
|   |   |   Names.cpp
|   |   |   Names.h
|   |   |   oui.h
|   |   |   Scan.cpp
|   |   |   Scan.h
|   |   |   settings.cpp
|   |   |   settings.h
|   |   |   SimpleList.h
|   |   |   SSIDs.cpp
|   |   |   SSIDs.h
|   |   |   Stations.cpp
|   |   |   Stations.h
|   |   |   webfiles.h
|   |   |   wifi.cpp
|   |   |   wifi.h
|   |   |
|   |   +---data
|   |   |   \---web
|   |   |       |   attack.html.gz
|   |   |       |   index.html.gz
|   |   |       |   info.html.gz
|   |   |       |   LICENSE.gz
|   |   |       |   scan.html.gz
|   |   |       |   settings.html.gz
|   |   |       |   ssids.html.gz
|   |   |       |   style.css.gz
|   |   |       |
|   |   |       +---js
|   |   |       |       attack.js.gz
|   |   |       |       scan.js.gz
|   |   |       |       settings.js.gz
|   |   |       |       site.js.gz
|   |   |       |       ssids.js.gz
|   |   |       |
|   |   |       \---lang
|   |   |               cn.lang.gz
|   |   |               cs.lang.gz
|   |   |               da.lang.gz
|   |   |               de.lang.gz
|   |   |               en.lang.gz
|   |   |               es.lang.gz
|   |   |               fi.lang.gz
|   |   |               fr.lang.gz
|   |   |               hu.lang.gz
|   |   |               in.lang.gz
|   |   |               it.lang.gz
|   |   |               ja.lang.gz
|   |   |               ko.lang.gz
|   |   |               nl.lang.gz
|   |   |               pl.lang.gz
|   |   |               pt-br.lang.gz
|   |   |               ptbr.lang.gz
|   |   |               ro.lang.gz
|   |   |               ru.lang.gz
|   |   |               th.lang.gz
|   |   |               tlh.lang.gz
|   |   |               uk.lang.gz
|   |   |
|   |   \---src
|   |       +---Adafruit_DotStar-1.1.4
|   |       |       Adafruit_DotStar.cpp
|   |       |       Adafruit_DotStar.h
|   |       |       license.txt
|   |       |
|   |       +---Adafruit_NeoPixel-1.7.0
|   |       |       Adafruit_NeoPixel.cpp
|   |       |       Adafruit_NeoPixel.h
|   |       |       COPYING
|   |       |       esp8266.c
|   |       |
|   |       +---ArduinoJson-v5.13.5
|   |       |       ArduinoJson.h
|   |       |
|   |       +---DS3231-1.0.3
|   |       |       DS3231.cpp
|   |       |       DS3231.h
|   |       |       LICENSE
|   |       |
|   |       +---esp8266-oled-ssd1306-4.1.0
|   |       |       license
|   |       |       OLEDDisplay.cpp
|   |       |       OLEDDisplay.h
|   |       |       OLEDDisplayFonts.h
|   |       |       OLEDDisplayUi.cpp
|   |       |       OLEDDisplayUi.h
|   |       |       README.md
|   |       |       SH1106.h
|   |       |       SH1106Brzo.h
|   |       |       SH1106Spi.h
|   |       |       SH1106Wire.h
|   |       |       SSD1306.h
|   |       |       SSD1306Brzo.h
|   |       |       SSD1306I2C.h
|   |       |       SSD1306Spi.h
|   |       |       SSD1306Wire.h
|   |       |
|   |       +---my92xx-3.0.3
|   |       |       LICENSE
|   |       |       my92xx.cpp
|   |       |       my92xx.h
|   |       |
|   |       \---SimpleButton
|   |           |   LICENSE
|   |           |   SimpleButton.h
|   |           |
|   |           +---Buttons
|   |           |       AnalogStick.cpp
|   |           |       AnalogStick.h
|   |           |       Button.cpp
|   |           |       Button.h
|   |           |       ButtonAnalog.cpp
|   |           |       ButtonAnalog.h
|   |           |       ButtonGPIOExpander.cpp
|   |           |       ButtonGPIOExpander.h
|   |           |       ButtonPullup.cpp
|   |           |       ButtonPullup.h
|   |           |       ButtonPullupGPIOExpander.cpp
|   |           |       ButtonPullupGPIOExpander.h
|   |           |       PS2Gamepad.cpp
|   |           |       PS2Gamepad.h
|   |           |       RotaryEncoder.cpp
|   |           |       RotaryEncoder.h
|   |           |       RotaryEncoderI2C.cpp
|   |           |       RotaryEncoderI2C.h
|   |           |       Switch.cpp
|   |           |       Switch.h
|   |           |
|   |           +---Events
|   |           |       ClickEvent.cpp
|   |           |       ClickEvent.h
|   |           |       DoubleclickEvent.cpp
|   |           |       DoubleclickEvent.h
|   |           |       Event.cpp
|   |           |       Event.h
|   |           |       HoldEvent.cpp
|   |           |       HoldEvent.h
|   |           |       PushEvent.cpp
|   |           |       PushEvent.h
|   |           |       ReleaseEvent.cpp
|   |           |       ReleaseEvent.h
|   |           |
|   |           \---libs
|   |                   GPIOExpander.cpp
|   |                   GPIOExpander.h
|   |                   MCP23017.cpp
|   |                   MCP23017.h
|   |                   PCF8574.cpp
|   |                   PCF8574.h
|   |                   PCF8575.cpp
|   |                   PCF8575.h
|   |
|   +---Reset_Sketch
|   |       blank_1MB.bin
|   |       README.md
|   |       reset_16mb.bin
|   |       reset_1mb.bin
|   |       reset_4mb.bin
|   |       reset_512kb.bin
|   |       Reset_Sketch.ino
|   |
|   +---utils
|   |   |   arduino-cli-compile.py
|   |   |
|   |   +---old_web_converter
|   |   |       converter.html
|   |   |       convert_all.sh
|   |   |       jquery-3.2.1.min.js
|   |   |       readme.md
|   |   |       style.css
|   |   |
|   |   +---vendor_list_updater
|   |   |       README.md
|   |   |       update_manuf.py
|   |   |
|   |   \---web_converter
|   |       |   readme.md
|   |       |   webConverter.py
|   |       |
|   |       \---css_html_js_minify
|   |               css_minifier.py
|   |               html_minifier.py
|   |               js_minifier.py
|   |               minify.py
|   |               variables.py
|   |               __init__.py
|   |
|   \---web_interface
|       |   attack.html
|       |   attack.json
|       |   index.html
|       |   info.html
|       |   names.json
|       |   run
|       |   scan.html
|       |   scan.json
|       |   settings.html
|       |   settings.json
|       |   ssids.html
|       |   ssids.json
|       |   style.css
|       |
|       +---js
|       |       attack.js
|       |       scan.js
|       |       settings.js
|       |       site.js
|       |       ssids.js
|       |
|       \---lang
|               cn.lang
|               cs.lang
|               da.lang
|               de.lang
|               en.lang
|               es.lang
|               fi.lang
|               fr.lang
|               hu.lang
|               in.lang
|               it.lang
|               ja.lang
|               ko.lang
|               nl.lang
|               pl.lang
|               ptbr.lang
|               ro.lang
|               ru.lang
|               th.lang
|               tlh.lang
|               uk.lang
|
+---main
|       main.ino
|       MotorControl.cpp
|       MotorControl.h
|       WebServer.cpp
|       WebServer.h
|
\---requirements
        deauther_docs.md
        ESP8266_docs.pdf
        integration_instructions.md
        motor_driver_instructions.md

## **Unified Project Structure**
```
ESP_INTEGRATED_PROJECT/
├── data/                       // Static files for the web interface
│   ├── joystick.html           // HTML for joystick control
│   ├── index.html.gz           // Home page for Deauther
│   ├── styles.css              // Shared styles
├── main/                       // Main application directory
│   ├── main.ino                // Entry point
│   ├── MotorControl.h          // Motor control header
│   ├── MotorControl.cpp        // Motor control implementation
│   ├── WebServer.h             // Web server header
│   ├── WebServer.cpp           // Web server implementation
├── deauther/                   // Deauther-specific functionality
│   ├── Scan.cpp                // Scanning logic
│   ├── Scan.h                  // Scanning header
│   ├── Attack.cpp              // Attack logic
│   ├── Attack.h                // Attack header
│   ├── wifi.cpp                // Wi-Fi utilities
│   ├── wifi.h                  // Wi-Fi utilities header
│   ├── settings.cpp            // Settings management
│   ├── settings.h              // Settings header
│   ├── webfiles.h              // Compressed web interface for Deauther
└── requirements/               // Documentation and references
    ├── ESP8266_docs.pdf        // ESP8266 reference
    ├── motor_driver_instructions.md
    ├── integration_instructions.md
```

---

## **Pin Configuration and Circuit Overview**

### **Pin Configuration**
- **Motor 1 Control**: GPIO 14 (D5)
- **Motor 2 Control**: GPIO 12 (D6)
- **Onboard LED**: GPIO 2 (LED_BUILTIN)
- **Wi-Fi Functions**: Pins used for Deauther functionalities are managed dynamically.

### **Circuit Description**
1. **Motor Control**:
   - TIP122 transistors are used to switch two DC motors.
   - Flyback diodes protect the circuit from back EMF.

2. **Power Supply**:
   - Separate power sources for the motors (5V USB) and the ESP8266 (via micro-USB).

3. **Deauther Functionality**:
   - Wi-Fi scanning and packet injection utilize internal ESP8266 capabilities without additional hardware.

---

## **Integration Steps**

### **1. Incorporate Necessary Deauther Files**
Copy the following Deauther files into the `deauther/` directory:
- `Scan.cpp` and `Scan.h`: Wi-Fi scanning logic.
- `Attack.cpp` and `Attack.h`: Deauthentication, beacon, and probe attack logic.
- `wifi.cpp` and `wifi.h`: Handles Wi-Fi initialization and packet injection.
- `settings.cpp` and `settings.h`: Manages user configurations.
- `webfiles.h`: Contains compressed web pages for Deauther functionalities.

### **2. Modify the Main Application**

#### **Global Mode Variable**
Add a global variable to manage the active mode:
```cpp
enum Mode { MOTOR_DRIVER, DEAUTHER };
Mode activeMode = MOTOR_DRIVER;
```

#### **Mode-Switching Functions**
Define functions to initialize and stop each mode:
```cpp
void switchToMotorDriver() {
    stopDeauther();
    initMotorDriver();
    activeMode = MOTOR_DRIVER;
}

void switchToDeauther() {
    stopMotorDriver();
    initDeauther();
    activeMode = DEAUTHER;
}
```

### **3. Web Server Integration**

#### **Add Routes for Mode Switching**
In `WebServer.cpp`, add routes to toggle between modes:
```cpp
server.on("/switch_to_motor", HTTP_GET, []() {
    switchToMotorDriver();
    server.send(200, "text/plain", "Switched to Motor Driver Mode");
});

server.on("/switch_to_deauther", HTTP_GET, []() {
    switchToDeauther();
    server.send(200, "text/plain", "Switched to Deauther Mode");
});
```

#### **Add Deauther-Specific Routes**
Integrate Deauther commands:
```cpp
server.on("/scan", HTTP_GET, []() {
    scan.start();
    server.send(200, "text/plain", "Scan started");
});

server.on("/attack", HTTP_GET, []() {
    attack.start(DEAUTH_MODE);
    server.send(200, "text/plain", "Deauth attack started");
});
```

#### **Update Home Page**
Modify `index.html` to include mode selection and dynamic content based on the active mode.

### **4. Resource Management**

#### **Wi-Fi Initialization**
Use `wifi.cpp` for AP setup:
```cpp
WiFi.softAP("ESP8266_Project", "password123");
```

#### **Memory Management**
Release unused resources when switching modes:
```cpp
scan.stop();
attack.stop();
```

---

## **Testing and Validation**

1. **Motor Driver Mode**:
   - Validate motor operations via the joystick web interface.
   - Check LED feedback for motor states.

2. **Deauther Mode**:
   - Test Wi-Fi scanning and attacks.
   - Confirm functionality through the Deauther web interface.

3. **Mode Switching**:
   - Toggle between modes and ensure seamless transitions.
   - Verify no GPIO or memory conflicts occur.

---

## **Expected Outcome**

- A unified ESP8266 system capable of motor control and network testing.
- Modular and scalable design for future feature additions.

---