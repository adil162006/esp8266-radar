ESP8266 Radar System 🚀
This project uses an ESP8266 microcontroller to create a simple radar system that:

Measures distance using an ultrasonic sensor (HC-SR04).

Displays the distance in real-time on a webpage hosted by the ESP8266.

Controls the built-in LED based on the detected distance.

Features ✨
📡 Real-time distance measurement

🌐 Built-in Web Server (ESP8266 hosts the webpage)

💡 LED turns ON if an object is detected within 20 cm

⚡ Light and fast webpage with live updates using JavaScript fetch()

Hardware Required 🛠
ESP8266 Board (like NodeMCU, Wemos D1 Mini)

HC-SR04 Ultrasonic Sensor

Jumper Wires

(Optional) Breadboard for connections

Wiring Diagram 🔌

HC-SR04 Pin	ESP8266 Pin
VCC	3.3V
GND	GND
TRIG	D6 (GPIO12)
ECHO	D5 (GPIO14)
🔵 Note: The HC-SR04 usually runs on 5V — if using 3.3V from ESP, the range might be reduced. Use a level shifter if needed.

How It Works 🧠
ESP8266 connects to your Wi-Fi.

Hosts a web server at its local IP address.

A webpage fetches the current distance every second and displays it.

If an object is detected closer than 20 cm, the ESP8266's built-in LED turns ON.

Web Interface Screenshot 🖥

(You can replace the above placeholder link with your own screenshot later.)

Code Highlights 🧩
server.on("/"): Serves the main webpage.

server.on("/distance"): Provides real-time distance data in JSON format.

pulseIn(): Measures the ultrasonic echo time to calculate distance.

Built-in LED logic based on distance.

Setup Instructions ⚙️
Install ESP8266 Board in Arduino IDE via Boards Manager.

Install ESP8266WebServer and ESP8266WiFi libraries (they usually come built-in).

Replace ssid and password in the code with your Wi-Fi credentials.

Upload the sketch to your ESP8266.

Open Serial Monitor (115200 baud) to find the IP address.

Open the IP address in your browser to see the live radar!
