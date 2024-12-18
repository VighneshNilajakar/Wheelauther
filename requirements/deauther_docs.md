## **Deauther Documentation: Detailed Reference for Project Integration**

---

### **1. Overview of Relevance**
The Deauther project allows the ESP8266 microcontroller to scan, manipulate, and test Wi-Fi networks. For your project, specific components of the Deauther code and functionality will be used to:
- Incorporate Wi-Fi control for motor operations.
- Build a modular system capable of toggling between **motor driver functionalities** and **network testing functionalities** (Deauther modes).

---

### **2. Key Functionalities Relevant to the Project**

#### **Wi-Fi Control Setup**
1. **Access Point Creation**:
   - The Deauther firmware creates a Wi-Fi access point, allowing devices to connect to the ESP8266.
   - **Relevant Files**:
     - `wifi_init.cpp`: Handles the initialization of Wi-Fi in **AP mode**.
     - `A_config.h`: Configures the SSID (`pwned`) and password (`deauther`).

2. **Web Server Integration**:
   - The built-in web server serves the control panel and processes HTTP requests for motor control or network tests.
   - **Relevant Files**:
     - `WebServer.cpp`: Implements routes for the web interface.
     - HTML and JavaScript files in the `data/` directory define the UI, which can be extended to add joystick controls or toggle buttons.

3. **Switching Modes**:
   - The firmware allows toggling between scanning, attacking, or idle modes, which can be adapted to switch between motor control and Deauther functionalities.

---

#### **Wi-Fi Scanning**
1. **Network Scanning**:
   - The Deauther scans for available Wi-Fi networks and client devices (stations).
   - **How It Works**:
     - Captures beacon and probe requests from access points and client devices.
   - **Relevant Files**:
     - `Scan.cpp`: Implements scanning logic and returns a list of networks.
     - `Accesspoints.cpp`: Manages the list of detected networks.
   - **Project Use**:
     - This functionality can serve as a diagnostic mode alongside motor control, showing nearby network details in the web interface.

---

#### **Deauthentication Attack**
1. **Core Functionality**:
   - Sends deauthentication packets to disconnect clients from their Wi-Fi networks.
   - **How It Works**:
     - Exploits the lack of authentication in deauthentication frames in the 802.11 protocol.
     - Packets are crafted and sent using `wifi_send_pkt_freedom()`.
   - **Relevant Files**:
     - `Attack.cpp`: Handles the deauthentication packet crafting and transmission.
     - `wifi_init.cpp`: Configures the ESP8266 in monitor mode for raw packet injection.
   - **Project Use**:
     - Although this feature is not directly related to motor control, understanding its integration can inform modular code design.

---

#### **Web Interface**
1. **UI Components**:
   - The Deauther’s web interface can be adapted for motor control commands (e.g., joystick-based navigation) while retaining the Deauther’s scanning and attack controls.
   - **Relevant Files**:
     - `scan.html.gz`: Displays scanned networks.
     - `attack.html.gz`: Provides options to perform attacks.
   - **Project Use**:
     - Extend these files to include joystick controls or buttons for motor operations.
     - Example:
       - A toggle button for switching between **motor control mode** and **network testing mode**.

2. **Web Server Routes**:
   - HTTP routes process user commands and trigger actions in the firmware.
   - **Relevant Files**:
     - `WebServer.cpp`: Defines routes like `/scan`, `/attack`, or custom routes for motor operations.
   - **Project Use**:
     - Add custom routes like `/motor_forward`, `/motor_stop` for controlling motors from the web interface.

---

#### **Status Feedback**
1. **Real-Time Updates**:
   - The Deauther provides real-time feedback on packet counts and scan results via the web interface.
   - **Relevant Files**:
     - `WebServer.cpp`: Sends status updates to the interface.
     - JavaScript in `data/` for dynamic updates.
   - **Project Use**:
     - Use similar logic to display motor states or telemetry data (e.g., active motor, direction).

2. **Onboard LED**:
   - The built-in LED on the ESP8266 indicates activity like scans or attacks.
   - **Project Use**:
     - Repurpose the LED to indicate motor control actions or mode switches.

---

### **3. Modular Code References**
To integrate Deauther functionalities while maintaining modularity, the following files and structures can serve as a blueprint:

#### **Core Files**
- `wifi_init.cpp`:
  - Responsible for initializing Wi-Fi and configuring the ESP8266 in AP or monitor mode.
- `A_config.h`:
  - Contains macros for configuring SSID, password, and timeout values.

#### **Scanning Files**
- `Scan.cpp`:
  - Implements the logic for detecting nearby access points and devices.
- `Accesspoints.cpp`:
  - Manages detected network details and provides them to the UI.

#### **Attack Files**
- `Attack.cpp`:
  - Handles packet crafting and transmission for deauthentication and other attacks.

#### **Web Server Files**
- `WebServer.cpp`:
  - Manages HTTP routes and serves the control interface.
- `data/` directory:
  - Stores static files (HTML, JavaScript) for the web interface.

---

### **4. Suggested Workflow**
1. **Adapt Wi-Fi Initialization**:
   - Use `wifi_init.cpp` to configure the ESP8266 in AP mode for motor control.
   - Retain monitor mode initialization for Deauther functionalities (to be integrated later).

2. **Customize Web Interface**:
   - Modify files in the `data/` directory to add joystick-based motor controls.
   - Add routes in `WebServer.cpp` to handle motor commands.

3. **Extend Scanning Logic**:
   - Use `Scan.cpp` to implement a diagnostic mode for displaying nearby networks alongside motor control.

4. **Plan for Modular Integration**:
   - Keep Deauther-related files separate from motor control logic for easier debugging and scalability.

---