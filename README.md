# 🏡 Smart Ghar (IoT Home Automation System)

![ESP8266](https://img.shields.io/badge/Board-ESP8266-blue.svg)
![Blynk 2.0](https://img.shields.io/badge/Platform-Blynk_2.0-brightgreen.svg)
![IRremote](https://img.shields.io/badge/Control-IR_Remote-red.svg)
![EEPROM](https://img.shields.io/badge/Feature-Memory_Retention-orange.svg)

**Smart Ghar** is a robust and highly scalable smart home automation project built using the ESP8266 (NodeMCU / D1 Mini) architecture. It allows users to control home appliances seamlessly via **Blynk 2.0 (WiFi)** and locally using an **IR (Infrared) Remote**. 

It handles network provisioning effortlessly using **Blynk Edgent** and actively remembers the appliance states even during power cuts via **EEPROM State Memory**.

---

## ✨ Key Features

- 🌐 **WiFi Control via Blynk 2.0**: Control appliances from anywhere in the world using your smartphone.
- 📶 **Dynamic WiFi Provisioning**: No hardcoded WiFi credentials in the code. Connect the board to your router seamlessly using the Blynk app's "Add Device" (Blynk Edgent) workflow.
- 📡 **Local IR Remote Control**: Works with cheap, ubiquitous 24-key IR remotes (NEC protocol). Perfect for times when the internet is down.
- 💾 **Power-Loss State Memory (EEPROM)**: Relays automatically restore to their last known state when the power comes back on.
- 🌩️ **Over-The-Air (OTA) Updates**: Update the board's firmware wirelessly via Blynk.Air.
- 🎛️ **Master ON / OFF**: Dedicated virtual and IR buttons to turn all relays ON or OFF simultaneously.
- ⚡ **Optimized Processing**: Optimized IR interrupt limits to prevent timer collisions with ESP8266's single-core WiFi background processing.

---

## 🛠️ Hardware Requirements

1. **ESP8266 Development Board** (NodeMCU or Wemos D1 Mini)
2. **4-Channel Relay Module** (Active LOW)
3. **IR Receiver Sensor** (e.g., TSOP1738 / VS1838B)
4. **24-Key IR Remote** (or any standard NEC protocol remote)
5. **Jumper Wires & 5V Power Supply**

---

## 📍 Pin Configuration / Wiring

| ESP8266 Pin | Component | Description |
| :--- | :--- | :--- |
| **D1 (GPIO 5)** | Relay 1 | Controls Appliance 1 |
| **D2 (GPIO 4)** | Relay 2 | Controls Appliance 2 |
| **D5 (GPIO 14)**| Relay 3 | Controls Appliance 3 |
| **D6 (GPIO 12)**| Relay 4 | Controls Appliance 4 |
| **D7 (GPIO 13)**| IR Receiver `OUT` | Reads IR hex signals |
| **5V / VIN** | Relay VCC / IR VCC | Power to components |
| **GND** | Relay GND / IR GND| Common ground |

---

## 📲 Blynk Virtual Pin Mapping

Set up your Blynk 2.0 Web Dashboard/Mobile App with these datastreams:

| Virtual Pin | Datastream Type | Widget Type | Purpose |
| :--- | :--- | :--- | :--- |
| **V1** | Integer (0-1) | Button (Push/Switch) | Button for Relay 1 |
| **V2** | Integer (0-1) | Button (Push/Switch) | Button for Relay 2 |
| **V3** | Integer (0-1) | Button (Push/Switch) | Button for Relay 3 |
| **V4** | Integer (0-1) | Button (Push/Switch) | Button for Relay 4 |
| **V9** | Integer (0-1) | Button (Push) | **Master ALL OFF** |
| **V10** | Integer (0-1) | Button (Push) | **Master ALL ON** |

---

## ⚙️ Software & Library Set-Up

Ensure you have the following installed in your Arduino IDE:
1. **ESP8266 Board Package** (v3.0.0+)
2. **Blynk Library** (v1.3.0+)
3. **IRremote Library** by Shirriff (v4.0.0+)
4. Standard **EEPROM** library (Built-in)

---

## 🚀 Installation & Deployment

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/sakxam-xeetri/Smart_Ghar.git
   ```
2. **Configure Blynk Settings**:
   Open `smar_ghar_esp/smar_ghar_esp.ino` and paste your Blynk Template ID and Device Name at the very top:
   ```cpp
   #define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
   #define BLYNK_DEVICE_NAME "Smart Ghar"
   ```
3. **Flash the Firmware**:
   - Connect your ESP8266.
   - Select NodeMCU 1.0 (ESP-12E Module) in the Arduino IDE.
   - Set Baud Rate to `115200`.
   - Click **Upload**.

4. **Connect to WiFi (Blynk Provisioning)**:
   - Once flashed, the ESP8266 will broadcast its own WiFi hotspot (e.g., `Blynk Smart Ghar-XXXX`).
   - Open the **Blynk IoT App** on your phone.
   - Tap **Add New Device** -> **Find Devices nearby**.
   - Follow the prompt to pass your home router credentials securely to the ESP8266.

---

## 🧠 Technical Deep-Dive

### Custom EEPROM Addressing
Blynk Edgent traditionally monopolizes the ESP8266's EEPROM footprint (`ConfigStore.h`) to retain network details after power offs. If generic user states are saved blindly, they either wipe network credentials or get overwritten dynamically.
* **The Fix**: The native codebase was augmented to allocate `512 bytes` (`EEPROM.begin(512)`). Network variables operate on lower offset bytes, and relay mapping offsets securely reside at addresses `500, 501, 502, and 503`.

### IR Decoding Optimization
Operating the Blynk Cloud layer involves continuous asynchronous WiFi payloads. These background tasks natively interrupt the strict microsecond timer logic required by generic IR Libraries—leading to completely garbled IR string outputs (Unrecognized commands).
* **The Fix**: Utilized `#define DECODE_NEC` explicitly. Enforcing exclusively NEC protocol definitions frees up CPU clock cycles significantly.

---

## 🤝 Contributing
Contributions, issues, and feature requests are highly welcome! Feel free to check the [issues page](https://github.com/sakxam-xeetri/Smart_Ghar/issues).

## 📄 License
This project is open-sourced under the **MIT License**.
