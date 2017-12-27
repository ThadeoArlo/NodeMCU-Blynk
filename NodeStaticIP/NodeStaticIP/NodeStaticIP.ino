
#include <ESP8266WiFi.h>

const char* ssid = "Teddy K"; // ssid
const char* pass = "teddy987987";// pass
IPAddress ip(192, 168, 1, 109); //set static ip
IPAddress gateway(192, 168, 1, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet

int outPin = 13; // GPIO13
int inPin = 2;

int stat1;

WiFiServer server(80);

void setup() {

  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT);
  digitalWrite(outPin, LOW);
  
  Serial.begin(115200);
  delay(10);


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


//  int stat1 = 0;
  if (request.indexOf("/outPin=on") != -1)  {
    digitalWrite(outPin, HIGH);
    stat1 = 1;
  }
  if (request.indexOf("/outPin=off") != -1)  {
    digitalWrite(outPin, LOW);
    stat1 = 0;

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
client.println("  </head>");
client.println("  <body>");
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
/// outPin part. GUI, etc
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
