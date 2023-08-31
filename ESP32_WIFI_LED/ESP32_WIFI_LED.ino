#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "yourSSID";      // WiFi network name
const char* password = "yourPASSWORD";  // WiFi password

const int ledPin = 4; // Pin connected to the LED on the ESP32 (GPIO 4)
bool ledState = false;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Copy and paste the IP address into your browser");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body style=\"display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0;\">";
    html += "<div style=\"text-align: center;\">";
    html += "<div style=\"background-color: #f0f0f0; padding: 20px; display: inline-block; border-radius: 10px;\">";
    html += "<h1 style=\"font-family: 'Calibri', sans-serif;\">ESP32 LED Control</h1>";
    html += "<button style=\"width: 100px; height: 100px; border-radius: 50%; font-size: 20px; background-color: ";
    html += ledState ? "red" : "green";
    html += "\" onclick=\"toggleLED();\">";
    html += ledState ? "OFF" : "ON";
    html += "</button>";
    html += "<script>";
    html += "function toggleLED() {";
    html += "var xhttp = new XMLHttpRequest();";
    html += "xhttp.open(\"GET\", \"/toggle\", true);";
    html += "xhttp.send();";
    html += "setTimeout(function() { location.href = '/'; }, 100);";
    html += "}";
    html += "</script>";
    html += "</div>";
    html += "</div>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    request->send(200, "text/plain", ledState ? "LED is OFF" : "LED is ON");
  });

  server.begin();
}

void loop() {
  
}
