/**********************************************************************************
 *  TITLE: Blynk 2.0 + IR control 4 Relays using ESP8266 (NodeMCU / D1 Mini)
 *  FEATURES: EEPROM memory, Master All-ON and All-OFF via IR & Blynk
 **********************************************************************************/

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL3BhMypVyV"
#define BLYNK_TEMPLATE_NAME "SmartGhar"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial

// Custom board configuration
#define USE_NODE_MCU_BOARD

#include <IRremote.h>
#include <EEPROM.h>

#define IR_RECV_PIN D7 // D7 (IR receiver pin)

IRrecv irrecv(IR_RECV_PIN);
decode_results results;

// define the GPIO connected with Relays
#define RelayPin1 D1  // D1 (GPIO5)
#define RelayPin2 D2  // D2 (GPIO4)
#define RelayPin3 D5  // D5 (GPIO14)
#define RelayPin4 D6  // D6 (GPIO12)

#define VPIN_BUTTON_1       V1 
#define VPIN_BUTTON_2       V2
#define VPIN_BUTTON_3       V3 
#define VPIN_BUTTON_4       V4
#define VPIN_BUTTON_ALL_OFF V9   // Master OFF Button
#define VPIN_BUTTON_ALL_ON  V10  // Master ON Button

// Relay State (1 = ON/LOW, 0 = OFF/HIGH)
int toggleState_1 = 0;
int toggleState_2 = 0;
int toggleState_3 = 0;
int toggleState_4 = 0;

#include "BlynkEdgent.h"

BLYNK_CONNECTED() {
  // We want to send the local EEPROM states back to Blynk Server so the app matches the physical relays
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, toggleState_1 == 1 ? LOW : HIGH);
  EEPROM.write(0, toggleState_1);
  EEPROM.commit();
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, toggleState_2 == 1 ? LOW : HIGH);
  EEPROM.write(1, toggleState_2);
  EEPROM.commit();
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, toggleState_3 == 1 ? LOW : HIGH);
  EEPROM.write(2, toggleState_3);
  EEPROM.commit();
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, toggleState_4 == 1 ? LOW : HIGH);
  EEPROM.write(3, toggleState_4);
  EEPROM.commit();
}

// Master OFF from Blynk
BLYNK_WRITE(VPIN_BUTTON_ALL_OFF) {
  if(param.asInt() == 1) {
    all_SwitchOff();
  }
}

// Master ON from Blynk
BLYNK_WRITE(VPIN_BUTTON_ALL_ON) {
  if(param.asInt() == 1) {
    all_SwitchOn();
  }
}

void all_SwitchOff(){
  toggleState_1 = 0; digitalWrite(RelayPin1, HIGH); Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); EEPROM.write(0, toggleState_1); delay(50);
  toggleState_2 = 0; digitalWrite(RelayPin2, HIGH); Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); EEPROM.write(1, toggleState_2); delay(50);
  toggleState_3 = 0; digitalWrite(RelayPin3, HIGH); Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); EEPROM.write(2, toggleState_3); delay(50);
  toggleState_4 = 0; digitalWrite(RelayPin4, HIGH); Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); EEPROM.write(3, toggleState_4); delay(50);
  EEPROM.commit();
}

void all_SwitchOn(){
  toggleState_1 = 1; digitalWrite(RelayPin1, LOW); Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); EEPROM.write(0, toggleState_1); delay(50);
  toggleState_2 = 1; digitalWrite(RelayPin2, LOW); Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); EEPROM.write(1, toggleState_2); delay(50);
  toggleState_3 = 1; digitalWrite(RelayPin3, LOW); Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); EEPROM.write(2, toggleState_3); delay(50);
  toggleState_4 = 1; digitalWrite(RelayPin4, LOW); Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); EEPROM.write(3, toggleState_4); delay(50);
  EEPROM.commit();
}

void ir_remote(){
  if (irrecv.decode(&results)) {
      switch(results.value) {
          case 0xFFD02F: // Button 1 (FLASH)
          toggleState_1 = !toggleState_1;
          digitalWrite(RelayPin1, toggleState_1 == 1 ? LOW : HIGH);
          Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
          EEPROM.write(0, toggleState_1);
          EEPROM.commit();
          break;

          case 0xFFF00F: // Button 2 (STROBE)
          toggleState_2 = !toggleState_2;
          digitalWrite(RelayPin2, toggleState_2 == 1 ? LOW : HIGH);
          Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
          EEPROM.write(1, toggleState_2);
          EEPROM.commit();
          break;

          case 0xFFC837: // Button 3 (FADE)
          toggleState_3 = !toggleState_3;
          digitalWrite(RelayPin3, toggleState_3 == 1 ? LOW : HIGH);
          Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
          EEPROM.write(2, toggleState_3);
          EEPROM.commit();
          break;

          case 0xFFE817: // Button 4 (SMOOTH)
          toggleState_4 = !toggleState_4;
          digitalWrite(RelayPin4, toggleState_4 == 1 ? LOW : HIGH);
          Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
          EEPROM.write(3, toggleState_4);
          EEPROM.commit();
          break;

          case 0xFFC03F: // Master ON ("ON" button)
          all_SwitchOn();
          break;

          case 0xFF40BF: // Master OFF ("OFF" button)
          all_SwitchOff();
          break;
      }
      irrecv.resume();
  }
}

void setup()
{
  Serial.begin(115200);

  EEPROM.begin(512);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  
  // Read LAST states from EEPROM
  toggleState_1 = EEPROM.read(0);
  toggleState_2 = EEPROM.read(1);
  toggleState_3 = EEPROM.read(2);
  toggleState_4 = EEPROM.read(3);

  // Fallback to default OFF if EEPROM has never been written properly (returns 255)
  if (toggleState_1 > 1) { toggleState_1 = 0; EEPROM.write(0, 0); }
  if (toggleState_2 > 1) { toggleState_2 = 0; EEPROM.write(1, 0); }
  if (toggleState_3 > 1) { toggleState_3 = 0; EEPROM.write(2, 0); }
  if (toggleState_4 > 1) { toggleState_4 = 0; EEPROM.write(3, 0); }
  EEPROM.commit();

  // Restore Relays exactly as before
  digitalWrite(RelayPin1, toggleState_1 == 1 ? LOW : HIGH);
  digitalWrite(RelayPin2, toggleState_2 == 1 ? LOW : HIGH);
  digitalWrite(RelayPin3, toggleState_3 == 1 ? LOW : HIGH);
  digitalWrite(RelayPin4, toggleState_4 == 1 ? LOW : HIGH);

  irrecv.enableIRIn(); // Enabling IR sensor
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  ir_remote(); //IR remote Control
}
