# Motor Driver Project: Ideation and Planning

## **Project Overview**

The Motor Driver Project involves creating a modular and efficient motor control system using the ESP8266 microcontroller. The system will:

1. Enable precise control of two DC motors for directional movement (forward, backward, left, right, and stop).
2. Use a web interface to control the motors via a local network, allowing interactive real-time motor commands.
3. Provide visual feedback for motor states using the onboard LED of the ESP8266 microcontroller.

This project focuses on creating a standalone motor driver module that is efficient, cost-effective, and easily extensible for future integration.

---

## **Feature Requirements**

### **Essential Features**

1. **Motor Control**:

   - Independent control of two DC motors (ON/OFF, directional movement).

2. **Web Interface**:

   - Interactive joystick-style controls for directional movement.
   - Visual feedback for motor states (e.g., active/inactive) using the onboard LED.

3. **Modular Design**:

   - Code structure with separate modules for motor control and web server logic.

4. **Status Indication**:

   - Onboard LED feedback for system states (e.g., setup complete, motor active).

---

## **Relevant Documentation**

1. **ESP8266 Documentation**:

   - Refer to `ESP8266_docs.pdf` in the `requirements` folder for detailed information on:
     - Wi-Fi module capabilities.
     - GPIO pin configurations and limitations.

---

## **Current File Structure**

```
ESP MOTOR DRIVER/
├── data/               // Static files for web interface
│   ├── joystick.html  // HTML for joystick control UI
│   └── styles.css     // CSS for web interface
├── main/             // Main application directory (Arduino sketch)
│   ├── main.ino      // Entry point
│   ├── MotorControl.h      // Motor control header
│   ├── MotorControl.cpp    // Motor control implementation
│   ├── WebServer.h         // Web server header
│   └── WebServer.cpp       // Web server implementation
└── requirements/     // Project documentation
    ├── ESP8266_docs.pdf
    └── motor_driver_instructions.md
```

### **Pin Configuration and Circuit Overview**

#### **Pin Configuration**:
- **Motor 1 Control**: GPIO 14 (D5)
- **Motor 2 Control**: GPIO 12 (D6)
- **Onboard LED**: GPIO 2 (LED_BUILTIN)

#### **High-Level Circuit Description**:
1. **Motor Control**:
   - Two DC motors are controlled using GPIO pins configured as outputs.
   - Each motor is connected to the ESP8266 through a MOSFET (or transistor) for switching.

2. **Power Supply**:
   - The motors are powered by an external 5V supply, and the ESP8266 is powered separately via USB or another 5V source.
   - A common ground connects the motor power supply and the ESP8266.

3. **Diode Protection**:
   - Each motor has a flyback diode across its terminals to protect the circuit from back EMF generated when the motor switches off.

---

Note: For Arduino IDE compatibility, all source files (.h and .cpp) must be in the same directory as the main sketch (main.ino). The drivers/ and web/ directories are removed, and their contents are moved to the main/ directory.

---