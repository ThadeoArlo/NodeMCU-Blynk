//This is the combination of the NodeMCU control via web browser using static IP
//and Bylnk Control and with PIR sensor
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";
const char* ssid = ""; // ssid
const char* pass = "";// pass

IPAddress ip(192, 168, 1, 109); //set static ip
IPAddress gateway(192, 168, 1, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet

int outPin = 13; // GPIO13
int pirPin = 2;
int stat1;
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
  
  Blynk.begin(auth, ssid, pass);

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
  Blynk.run();
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

  int stat1 = 0;
  if (request.indexOf("/outPin=on") != -1)  {
    digitalWrite(outPin, HIGH);
    stat1 = 1;
  }
  if (request.indexOf("/outPin=off") != -1)  {
    digitalWrite(outPin, LOW);
    stat1 = 0;  
}

  
  pirValue = digitalRead(pirPin);
  if (pirValue) { 
    if (stat1 = 0) {
      digitalWrite(outPin, HIGH);
      }
  } else {
    digitalWrite(outPin, LOW);
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
if (stat1 == 1) {
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
