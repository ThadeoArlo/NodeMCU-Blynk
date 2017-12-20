//This is the combination of the NodeMCU control via web browser using static IP and Bylnk Control


#include <ESP8266WiFi.h>
 
const char* ssid = "Teddy K"; // ssid
const char* password = "teddy987987";// password
IPAddress ip(192, 168, 1, 109); //set static ip
IPAddress gateway(192, 168, 1, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet
 
int led1 = 13; // GPIO13
int led2 = 15; // GPIO15
int stat1;
int stat2;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
 
  // Connection to wireless network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
 
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
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // engine
 

  int stat1 = 0;
  if (request.indexOf("/led1=on") != -1)  {
    digitalWrite(led1, HIGH);
    stat1 = 1;
  }
  if (request.indexOf("/led1=off") != -1)  {
    digitalWrite(led1, LOW);
    stat1 = 0;
  }  
  int stat2 = 0;
  if (request.indexOf("/led2=on") != -1)  {
    digitalWrite(led2, HIGH);
    stat2 = 1;
  }
  if (request.indexOf("/led2=off") != -1)  {
    digitalWrite(led2, LOW);
    stat2 = 0;
  }  

 
  // Return the response
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
client.println("      <a href=\"/led1=on\">");
client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-yellow2 sq-card-padding\">");
client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">ON</h1>");
client.println("        </div>");
client.println("      </a>");
client.println("    </div>");
client.println("    <div class=\"sq-container-halfs sq-bg-gray1\">");
client.println("      <a href=\"/led1=off\">");
client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-blue3 sq-card-padding\">");
client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">OFF</h1>");
client.println("        </div>");
client.println("      </a>");
client.println("    </div>"); 
/// led1 part. GUI, etc
  client.print("Lights is now ");
  if(stat1 == 1) {
    client.print("On");
  } else {
    client.print("Off");
  }
  
  client.println("<!DOCTYPE HTML>");
//  client.println("<head>");
//  client.println("<meta charset='UTF-8'>");
//  client.println("<style>");
//  client.println(" a {background:#F44336; color:white; padding:25px; text-decoration:none; display:inline-block; width:50%; margin: 20px; text-align:center;}");
//  client.println("</style>");
//  client.println("</head>");
//  client.println("<html>");
//  client.println("<div align=\"center\">");
// /// led1 part. GUI, etc
//  client.print("LED je sada ");
//  if(stat1 == 1) {
//    client.print("upaljena");
//  } else {
//    client.print("ugašena");
//  }
//  client.println("<br><br>");
//  client.println("<a href=\"/led1=on\" >On </a>");
//  client.println("<a href=\"/led1=off\">Off </a><br />");
//  client.println("<br><br>");
//



  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
