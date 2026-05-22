/*
 * IR Remote HEX Code Finder for ESP8266
 * -------------------------------------
 * Upload this sketch to your ESP8266 to read the HEX codes 
 * from any IR Remote control.
 */

#include <IRremote.h>

// Define the IR receiver pin. We used D7 in the main project.
#define IR_RECV_PIN D7 

IRrecv irrecv(IR_RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  
  // Initialize the built-in LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // ESP8266 built-in LED is active LOW (HIGH means OFF)
  
  // Initialize the IR receiver
  irrecv.enableIRIn(); 
  
  Serial.println();
  Serial.println("---------------------------------");
  Serial.println("    IR HEX Code Reader Started   ");
  Serial.println("---------------------------------");
  Serial.println("Point your remote at the receiver and press a button...");
}

void loop() {
  // Check if an IR signal has been received
  if (irrecv.decode(&results)) {
    
    // Turn ON the built-in LED to visually indicate signal reception
    digitalWrite(LED_BUILTIN, LOW); 
    
    // Ignore the repeat code (usually FFFFFFFF for continuous hold)
    if (results.value != 0xFFFFFFFF) {
      Serial.print("Button Pressed. HEX Code: 0x");
      Serial.println(results.value, HEX); // Print the HEX code to Serial Monitor
    }
    
    delay(50); // Keep LED on briefly so we can clearly see the flash
    digitalWrite(LED_BUILTIN, HIGH); // Turn OFF the built-in LED
    
    // Resume listening for the next signal
    irrecv.resume();  
  }
}