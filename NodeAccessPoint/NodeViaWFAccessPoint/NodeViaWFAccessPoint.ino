/*
 * NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
 * to control GPIO (on-board LED)
 * Connect to AP "arduino-er", password = "password"
 * Open browser, visit 192.168.4.1
 */


 /*CAN ALSO BE USED AS VIA WEB BROWSER GOTO 192.168.1.13*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


const char *ssid = "Actinomycetes";
const char *password = "dictyosteliumdiscoideum";
int stateLed = LOW;
int ledPin = 13;
ESP8266WebServer server(80);

void handleRoot() {
    response();
}

void handleLedOn() {
  stateLed = LOW;
  digitalWrite(ledPin, stateLed);
  response();
}

void handleLedOff() {
  stateLed = HIGH;
  digitalWrite(ledPin, stateLed);
   response();
}

const String htmlTop = "<html style=\"text-align: center;\"><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String htmlTopClose = "</html>";
const String HtmlTitle = "<h1>Actinomycetes</h1><br/><p> aka \"Thing Onliner\" aka Websocket, literaly</p>\n";
const String HtmlLedStateLow = "<big>The Thing is now <b>ON</b></big><br/>\n";
const String HtmlLedStateHigh = "<big>The Thing is now <b>OFF</b></big><br/>\n";
const String HtmlButtons = 
    "<span><a href=\"LEDOn\"><button style=\"display: block; width: 100%; fontsize: 5em;\">ON</button></a><br/></span>"
    "<span><a href=\"LEDOff\"><button style=\"display: block; width: 100%; fontsize: 5em;\">OFF</button></a><br/></span>";

void response(){
  String htmlRes = htmlTop + HtmlTitle;
  if(stateLed == LOW){
    htmlRes += HtmlLedStateLow; 
  }else{
    htmlRes += HtmlLedStateHigh;
  }

  htmlRes += HtmlButtons;
  htmlRes += "</html>";

  server.send(200, "text/html", htmlRes);
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/LEDOn", handleLedOn);
    server.on("/LEDOff", handleLedOff);
    server.begin(); 
    Serial.println("HTTP server beginned");
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, stateLed);
}

void loop() {
    server.handleClient();
}
