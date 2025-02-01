# ESP32 IP Finder and MAC Address Displayer

This project allows you to retrieve the **IP address** and **MAC address** of an ESP32 when connected to a Wi-Fi network. The ESP32 prints these details to the Serial Monitor.

## 📌 Features
- Connects ESP32 to a Wi-Fi network
- Retrieves and displays the **IP Address**
- Retrieves and displays the **MAC Address**
- Prints details to the **Serial Monitor**

## 🛠️ Components Required
- ESP32 Development Board
- USB Cable
- Computer with Arduino IDE

## 📝 Installation & Setup

1. **Install ESP32 Board Support in Arduino IDE**  
   - Open Arduino IDE.
   - Go to `File` > `Preferences`.
   - Add the following URL in **Additional Board Manager URLs**:  
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Open `Boards Manager` (`Tools` > `Board` > `Boards Manager`).
   - Search for **ESP32** and install the latest version.

