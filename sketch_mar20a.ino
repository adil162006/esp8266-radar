#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Shravanya";
const char* password = "shravanya<3";

ESP8266WebServer server(80);

const int trigPin = 12; // D6
const int echoPin = 14; // D5
#define LED_PIN 2  // Built-in LED on ESP8266 (D4, active-low)

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // Ensure LED is OFF initially (active-low)

    server.on("/", handleRoot);
    server.on("/distance", handleDistance);
    server.begin();
}

void loop() {
    server.handleClient();

    int distance = getDistance(); // Get updated distance

    if (distance < 20) { 
        digitalWrite(LED_PIN, LOW);  // Turn LED ON (active-low)
    } else { 
        digitalWrite(LED_PIN, HIGH); // Turn LED OFF
    }
}

void handleRoot() {
    String html = "<!DOCTYPE html><html><head><title>ESP8266 Radar</title>";
    html += "<script>\n";
    html += "setInterval(function() {\n";
    html += "  fetch('/distance')\n";
    html += "    .then(response => response.json())\n";
    html += "    .then(data => {\n";
    html += "      document.getElementById('distance').innerText = data.distance;\n";
    html += "    });\n";
    html += "}, 1000);\n";
    html += "</script></head><body>";
    html += "<h1>ESP8266 Radar System</h1>";
    html += "<p>Distance: <span id='distance'>0</span> cm</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleDistance() {
    int distance = getDistance();
    String json = "{\"distance\": " + String(distance) + "}";
    server.send(200, "application/json", json);
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}

long getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);  // Timeout 30ms (to avoid lockup)
    if (duration == 0) return 400; // No echo detected, assume max distance
    return duration * 0.034 / 2; // Convert to cm
}