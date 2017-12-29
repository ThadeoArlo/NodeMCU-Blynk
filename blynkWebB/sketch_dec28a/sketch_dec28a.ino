//This is the combination of the NodeMCU control via web browser using static IP
//and Bylnk Control and with PIR sensor
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "f57a7459e8f54aef88b0a3a5259fc6cd";
const char* ssid = "Teddy K"; // ssid
const char* pass = "teddy987987";// pass

IPAddress ip(192, 168, 1, 109); //set static ip
IPAddress gateway(192, 168, 1, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet

int outPin = 13; // GPIO13
int pirPin = 2;
int stat_web;
int stat_pir;
int pirValue;

//#define outPin D7 
//#define pirPin D4

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(outPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(outPin, LOW);
  
//  Blynk.begin(auth, ssid, pass);

  // Connection to wireless network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  // Print the IP address in serial monitor. It must be the same we entered above
  Serial.print("Type this address in URL to connect: ");
  Serial.print("http://");
  Serial.println(ip);
  Serial.println("/");
}

void loop() {
//  Blynk.run();
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


//  int stat_web = HIGH;
  if (request.indexOf("/outPin=on") != -1)  {
    stat_web = HIGH;
  }
  if (request.indexOf("/outPin=off") != -1)  {
    stat_web = LOW;  
  }
  


//  pirValue = digitalRead(pirPin);
//  if (stat_pir == HIGH) {
//    digitalWrite(outPin, HIGH);
//    delay(120000); // 60000ms = 1 minute, set how long you want the output to be.
//
//    if (stat_pir == LOW) {
//      Serial.println("Motion Detected!");
////      stat_pir = HIGH;
//    }
//  } else {
//      digitalWrite(stat_pir, LOW);
//      delay(300);
//      if (stat_pir == HIGH){
//      Serial.println("No Motion");
////      stat_pir = LOW;
//    }
//  }


if (stat_web == HIGH) {
    digitalWrite(outPin, LOW);
  } else {
    digitalWrite(outPin, stat_pir);
  }




client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");

client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("  <head>");
client.println("    <meta charset=\"utf-8\">");
client.println("    <title>HomeIot</title>");
client.println("    <link rel=\"stylesheet\" href=\"http://arlora.co.nf/projects/libs/squared/sq.min.css\"/>");
//client.println("    <script src=\"http://ajax.googleapis.com/ajax/libs/angularjs/1.4.8/angular.min.js\"></script>");
client.println("  </head>");
//client.println("  <body onload=\"startDictation()\">");
client.println("  <body>");
//client.println("    <script src=\"//cdnjs.cloudflare.com/ajax/libs/annyang/2.4.0/annyang.min.js\"></script>");
client.println("    <div class=\"sq-container-halfs sq-bg-gray1\">");
client.println("      <a href=\"/outPin=on\">");
client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-yellow2 sq-card-padding\">");
client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">ON</h1>");
client.println("        </div>");
client.println("      </a>");
client.println("    </div>");
client.println("    <div class=\"sq-container-halfs sq-bg-gray1\">");
client.println("      <a href=\"/outPin=off\">");
client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-blue3 sq-card-padding\">");
client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">OFF</h1>");
client.println("        </div>");
client.println("      </a>");
client.println("    </div>");

client.print("Lights is now ");
if (stat_web == HIGH) {
  client.print("On");
} else {
  client.print("Off");
}

client.println("<!DOCTYPE HTML>");
client.println("</html>");
delay(1);
Serial.println("Client disonnected");
Serial.println("");
}
