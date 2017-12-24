#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>

//char ssid[] = "Teddy K";
//char pass[] = "teddy987987";
//char auth[] = "f57a7459e8f54aef88b0a3a5259fc6cd";

#define ledPin D7 
#define pirPin D4 // Input for HC-S501
int pirValue; // Place to store read PIR Value

void setup()
{
  Serial.begin(115200);
  delay(10);
//  Blynk.begin(auth, ssid, pass);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop()
{
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    digitalWrite(ledPin, HIGH);
    Serial.println("==> Motion detected");
    delay(100);
//    Blynk.notify("==> Motion detected");  
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("==>NO Motion detected");
    delay(100);
   }
//  Blynk.run();
}

