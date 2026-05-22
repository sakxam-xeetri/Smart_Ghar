/**********************************************************************************
 *  TITLE: Blynk 2.0 + IR control 4 Relays using ESP8266 (NodeMCU / D1 Mini)
 **********************************************************************************/

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial

// Custom board configuration
#define USE_NODE_MCU_BOARD

#include <IRremote.h>

#define IR_RECV_PIN D7 // D7 (IR receiver pin)

IRrecv irrecv(IR_RECV_PIN);
decode_results results;

// define the GPIO connected with Relays
#define RelayPin1 D1  // D1 (GPIO5)
#define RelayPin2 D2  // D2 (GPIO4)
#define RelayPin3 D5  // D5 (GPIO14)
#define RelayPin4 D6  // D6 (GPIO12)

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4
#define VPIN_BUTTON_C    V9

// Relay State
bool toggleState_1 = HIGH;
bool toggleState_2 = HIGH;
bool toggleState_3 = HIGH;
bool toggleState_4 = HIGH;

#include "BlynkEdgent.h"

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, toggleState_1 == 1 ? LOW : HIGH);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, toggleState_2 == 1 ? LOW : HIGH);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, toggleState_3 == 1 ? LOW : HIGH);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, toggleState_4 == 1 ? LOW : HIGH);
}

BLYNK_WRITE(VPIN_BUTTON_C) {
  all_SwitchOff();
}

void all_SwitchOff(){
  toggleState_1 = 0; digitalWrite(RelayPin1, HIGH); Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); delay(100);
  toggleState_2 = 0; digitalWrite(RelayPin2, HIGH); Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); delay(100);
  toggleState_3 = 0; digitalWrite(RelayPin3, HIGH); Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); delay(100);
  toggleState_4 = 0; digitalWrite(RelayPin4, HIGH); Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); delay(100);
}

void ir_remote(){
  if (irrecv.decode(&results)) {
      switch(results.value) {
          case 0x1FE50AF: // Button 1
          digitalWrite(RelayPin1, !digitalRead(RelayPin1));
          toggleState_1 = !digitalRead(RelayPin1);
          Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1 == LOW ? 1 : 0);
          break;
          case 0x1FED827: // Button 2
          digitalWrite(RelayPin2, !digitalRead(RelayPin2));
          toggleState_2 = !digitalRead(RelayPin2);
          Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2 == LOW ? 1 : 0);
          break;
          case 0x1FEF807: // Button 3
          digitalWrite(RelayPin3, !digitalRead(RelayPin3));
          toggleState_3 = !digitalRead(RelayPin3);
          Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3 == LOW ? 1 : 0);
          break;
          case 0x1FE30CF: // Button 4
          digitalWrite(RelayPin4, !digitalRead(RelayPin4));
          toggleState_4 = !digitalRead(RelayPin4);
          Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4 == LOW ? 1 : 0);
          break;
      }
      irrecv.resume();
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  
  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  irrecv.enableIRIn(); // Enabling IR sensor
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  ir_remote(); //IR remote Control
}
