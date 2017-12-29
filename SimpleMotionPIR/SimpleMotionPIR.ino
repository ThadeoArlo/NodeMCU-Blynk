#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>

#define outPin D7 
#define pirPin D4 // Input for HC-S501
//int pirValue; // Place to store read PIR Value
int pirValue;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(outPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(outPin, LOW);
}

void loop() {
  pirValue = digitalRead(pirPin);
  if (pirValue) { 
    digitalWrite(outPin, HIGH);
//    Serial.println("==> Motion detected");
    delay(100);
  } else {
    digitalWrite(outPin, LOW);
//    Serial.println("==>NO Motion detected");
    delay(100);
   }
}

