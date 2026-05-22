# Smart Home Automation with ESP8266, Blynk IoT, and IR Remote

This project provides a robust and offline-capable smart home automation system using the ESP8266 (NodeMCU or Wemos D1 Mini). It allows you to control 4 relays via the robust **Blynk IoT platform** (from anywhere in the world) and via an **IR Remote Control** (for offline and fast local access).

## Features

*   **ESP8266 Powered:** Uses the cost-effective NodeMCU or Wemos D1 Mini boards.
*   **4-Channel Relay Control:** Manage up to 4 distinct electrical appliances.
*   **Blynk 2.0 Integration:** Monitor and control devices seamlessly through the Blynk Web Dashboard and Mobile App.
*   **Blynk Edgent Provisioning:** No need to hardcode WiFi credentials! Setup your WiFi quickly via the Blynk App over a secure AP.
*   **IR Remote Control:** Fully functioning local fallback. You can toggle relays using a standard IR remote control (e.g., TSOP1838 receiver).
*   **Real-Time Sync:** Turning on a switch via the IR remote updates the Blynk app instantly.
*   **EEPROM Power-State Memory:** Automatically remembers and strictly restores the exact relay states (on/off) immediately after a power cut, before WiFi even connects.

---

## Hardware Requirements

1. **ESP8266 Board** (NodeMCU V2/V3 or Wemos D1 Mini)
2. **4-Channel Relay Module** (5V active low is standard)
3. **IR Receiver Sensor** (e.g., TSOP1838 or HX1838)
4. Jumper Wires & Breadboard
5. 5V Power Supply (Recommended for powering relays)

---

## Circuit Diagram & Pin Connections

| ESP8266 Pin | Component | Description |
| :--- | :--- | :--- |
| **D1 (GPIO5)** | Relay 1 | Controls Appliance 1 |
| **D2 (GPIO4)** | Relay 2 | Controls Appliance 2 |
| **D5 (GPIO14)**| Relay 3 | Controls Appliance 3 |
| **D6 (GPIO12)**| Relay 4 | Controls Appliance 4 |
| **D7 (GPIO13)**| IR Receiver | Connect to the OUT/DATA pin of the IR sensor |
| **D3 (GPIO0)** | Built-in Flash Button | Hold for 10 seconds to reset WiFi credentials |
| **D4 (GPIO2)** | Built-in LED | Displays the network connecting/pairing status |

*Note: Most relay modules are Active LOW, meaning a LOW signal turns the relay ON. The code handles this logic natively.*

---

## Software Requirements

1. **Arduino IDE** (v1.8.x or v2.x)
2. **ESP8266 Board Package**: Install via Arduino IDE Board Manager (http://arduino.esp8266.com/stable/package_esp8266com_index.json).
3. **Libraries**:
   *   Blynk by Volodymyr Shymanskyy (Version 1.2.0 or newer)
   *   IRremote by shirriff (Version 3.x.x or newer)

---

## Setup & Configuration

### Step 1: Blynk Cloud Setup
1. Go to your [Blynk Console](https://blynk.cloud) and create a **New Template**.
2. Go to the **Datastreams** tab within your template and create the following Virtual Pins (Integer, Min:0, Max:1):
   *   V1 -> Relay 1 Button
   *   V2 -> Relay 2 Button
   *   V3 -> Relay 3 Button
   *   V4 -> Relay 4 Button
   *   V9 -> All Off Button
3. Go to exactly **Web Dashboard** and/or **Mobile App** and map button widgets to these Virtual Pins.
4. Save the template, navigate to **Search -> My Devices**, and create a **New Device** based on this template.

### Step 2: Code Configuration
1. In the smar_ghar_esp.ino file, find the following lines at the very top:
   `cpp
   #define BLYNK_TEMPLATE_ID "TMPL_xxxxx"
   #define BLYNK_DEVICE_NAME "My Smart Home"
   `
2. Replace them with the exact firmware configuration text provided by Blynk in your device's info panel.

### Step 3: IR Remote Configuration (Optional)
If your IR remote uses different HEX codes:
1. Open the Arduino IDE Serial Monitor (115200 baud).
2. Point your remote at the receiver and press buttons.
3. Note the HEX codes that print out in standard IR scripts, and update the switch(results.value) block inside the ir_remote() function in smar_ghar_esp.ino.

### Step 4: Flashing the Code
1. Connect your ESP8266 to your PC via a Micro-USB/USB-C cable.
2. Select your board (e.g., NodeMCU 1.0 (ESP-12E Module)) and correct COM port in Arduino IDE.
3. Hit **Upload**.

### Step 5: Network Provisioning (Blynk Edgent)
1. Since we are using Blynk Edgent, you **do not** put your WiFi SSID and Password in the code!
2. Open the **Blynk Mobile App** on your smartphone.
3. Tap **Add Device** -> **Find Devices nearby**.
4. The app will connect to the ESP8266's temporary Access Point (AP) named Blynk xxx.
5. Enter your home WiFi network credentials within the app to strictly pair the device.
6. Once connected, the built-in LED will breathe/beat smoothly, indicating it is connected to the cloud.

---

## Troubleshooting

- **Relays turning ON at startup:** Ensure your relay board is 5V-powered correctly. The code brings pins to HIGH automatically on startup to prevent triggering active-low relays.
- **Can't connect to WiFi:** Hold the Flash button on the NodeMCU (connected to D3/GPIO0) for 10 full seconds to wipe saved WiFi credentials and restart the pairing process.
- **IR Not working:** Ensure the IR sensor is wired correctly: VCC -> 3.3V, GND -> GND, OUT -> D7.

## OTA Updates (Blynk.Air)
Since the project uses Blynk Edgent, Over-The-Air (OTA) updates are already built-in via the Blynk Cloud! You can update your ESP8266 wirelessly from anywhere in the world.

### How to use Blynk OTA:
1. In your code, increment the firmware version (e.g., change `#define BLYNK_FIRMWARE_VERSION "0.1.0"` to `"0.1.1"`).
2. In Arduino IDE, go to **Sketch > Export compiled Binary**.
3. Open the **Blynk Web Console**, navigate to **Blynk.Air** (the cloud uploading icon).
4. Click **New Shipping**, select your device, and upload the generated `.bin` file.
5. The ESP8266 will automatically download the new firmware, restart, and apply the update without any cables.

Happy Automating!
