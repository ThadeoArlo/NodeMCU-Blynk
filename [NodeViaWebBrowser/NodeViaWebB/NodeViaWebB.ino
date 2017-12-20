 #include <ESP8266WiFi.h>
 
const char* ssid = "Teddy K";
const char* password = "teddy987987";
 
int ledPin = 13; // GPIO13
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
digitalWrite(ledPin, value);
 
//   Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one
//
//
//client.println("HTTP/1.1 200 OK"); 
//client.println("Content-Type: text/html"); 
//client.println("Access-Control-Allow-Origin: *"); 
//client.println(""); //  do not forget this one
//
//client.println("<!DOCTYPE html>");
//client.println("<html>");
//client.println("  <head>");
//client.println("    <meta charset=\"utf-8\">");
//client.println("    <title>Appl2</title>");
//client.println("  </head>");
//client.println("  <body>");
//client.println("    <p>");
//client.println("    test");
//client.println("    </p>");
//client.println("    <script>");
//client.println("      function apple() {");
//client.println("        window.alert('helllooooo yayy it workss');");
//client.println("      }");
//client.println("    </script>");
//client.println("  </body>");
//client.println("</html>");


//  client.println("<!DOCTYPE HTML>");
//  client.println("<html>");
// 
//  client.print("Led pin is now: ");
// 
//  if(value == HIGH) {
//    client.print("On");
//  } else {
//    client.print("Off");
//  }
//  client.println("<br><br>");
//  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
//  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
//  client.println("</html>");



//client.println("<!DOCTYPE html>");
//client.println("<html>");
//client.println("  <head>");
//client.println("    <meta charset=\"utf-8\">");
//client.println("    <title>HomeIot</title>");
//client.println("    <link rel=\"stylesheet\" href=\"http://arlora.co.nf/projects/libs/squared/sq.min.css\"/>");
//client.println("  </head>");
//client.println("  <body>");
//client.println("    <div class=\"sq-container-halfs sq-bg-green2\">");
//client.println("      <a href=\"/LED=ON\">");
//client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-yellow2 sq-card-padding\">");
//client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">ON</h1>");
//client.println("        </div>");
//client.println("      </a>");
//client.println("    </div>");
//client.println("    <div class=\"sq-container-halfs sq-bg-green2\">");
//client.println("      <a href=\"/LED=OFF\">");
//client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-blue3 sq-card-padding\">");
//client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">OFF</h1>");
//client.println("        </div>");
//client.println("      </a>");
//client.println("    </div>");
//client.print("Led pin is now: ");


//
//client.println("<!DOCTYPE html>");
//client.println("<html>");
//client.println("  <head>");
//client.println("    <meta charset=\"utf-8\">");
//client.println("    <title>HomeIot</title>");
//client.println("    <link rel=\"stylesheet\" href=\"http://arlora.co.nf/projects/libs/squared/sq.min.css\"/>");
//client.println("  </head>");
//client.println("  <body>");
//client.println("    <div class=\"sq-container-halfs sq-bg-gray1\">");
//client.println("      <a href=\"/LED=ON\">");
//client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-yellow2 sq-card-padding\">");
//client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">ON</h1>");
//client.println("        </div>");
//client.println("      </a>");
//client.println("    </div>");
//client.println("    <div class=\"sq-container-halfs sq-bg-gray1\">");
//client.println("      <a href=\"/LED=OFF\">");
//client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-blue3 sq-card-padding\">");
//client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">OFF</h1>");
//client.println("        </div>");
//client.println("      </a>");
//client.println("    </div>");
//client.println("    <button onclick=\"window.location.assign('http://google.com')\">apple pie</button>");
//client.print("Led pin is now: ");


//____________________________________________________________________________________


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
client.println("      <a href=\"/LED=ON\">");
client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-yellow2 sq-card-padding\">");
client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">ON</h1>");
client.println("        </div>");
client.println("      </a>");
client.println("    </div>");
client.println("    <div class=\"sq-container-halfs sq-bg-gray1\">");
client.println("      <a href=\"/LED=OFF\">");
client.println("        <div class=\"sq-card-halfs sq-card-btn sq-bg-blue3 sq-card-padding\">");
client.println("          <h1 class=\"sq-textcolor-white sq-undraggable\">OFF</h1>");
client.println("        </div>");
client.println("      </a>");
client.println("    </div>");

client.println("<script>");
client.println("  function on() {");
//client.println("    window.location.assign(window.location.href + \"/LED=ON\")");
client.println("    location.replace(window.location.href + \"/LED=ON\")");
//client.println("    location.replace('192.168.1.29/LED=ON')");
client.println("  }");
client.println("  function off() {");
//client.println("    window.location.assign(window.location.href + \"/LED=OFF\")");
client.println("    location.replace(window.location.href + \"/LED=OFF\")");
//client.println("    location.replace('192.168.1.29/LED=OFF')");
client.println("  }");
client.println("</script>");








//client.println("    <script>");
//client.println("      if (annyang) {");
//client.println("        annyang.addCommands({");
//client.println("          'apple': function () {");
//client.println("            alert('APPLE WORLD!');");
//client.println("          }");
//client.println("        });");
//client.println("        annyang.addCommands({");
//client.println("          'turn on': function () {");
//client.println("            window.open(window.location.href + \"//LED=OFF\");");
//client.println("          }");
//client.println("        });");
//client.println("        annyang.addCommands({");
//client.println("          'apple': function () {");
//client.println("            window.open(window.location.href + \"//LED=ON\");");
//client.println("          }");
//client.println("        });");
//client.println("        annyang.start();");
//client.println("      }");
//client.println("    </script>");


if(value == HIGH) {
  client.print("On");
} else {
  client.print("Off");
}
client.println("  </body>");
client.println("</html>");
client.println("");



 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
