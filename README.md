# 📷 ESP32-CAM Motion Detection & Email Alert System

A smart security and surveillance system built using an **ESP32-CAM**, **PIR motion sensor**, **BC547 transistor**, and **LED**.

The system detects motion using the PIR sensor, captures an image using the ESP32-CAM, sends the captured image to an email address, and provides a live camera view through a web browser.

---

## 🚀 Features

* 📷 **ESP32-CAM** for image capture and live video streaming
* 🚶 **PIR sensor** for motion detection
* 📧 **Email alert** with a captured image when motion is detected
* 🌐 **Live camera view** through a web browser
* 💡 **LED indication** when motion is detected
* 🔌 **BC547 transistor** used to control the LED
* 📡 Wi-Fi connectivity
* ⏱️ Motion alert delay to prevent repeated email notifications

---

## 🧰 Components Required

| Component             |    Quantity |
| --------------------- | ----------: |
| ESP32-CAM             |           1 |
| PIR Sensor (HC-SR501) |           1 |
| BC547 Transistor      |           1 |
| LED                   |           1 |
| 330Ω Resistor         |           1 |
| 1kΩ Resistor          |           1 |
| Jumper Wires          | As required |
| 5V Power Supply       |           1 |

---

## 🔌 Circuit Connections

### PIR Sensor → ESP32-CAM

| PIR Sensor | ESP32-CAM |
| ---------- | --------- |
| VCC        | 5V        |
| GND        | GND       |
| OUT        | GPIO 13   |

### BC547 + LED → ESP32-CAM

| Component         | Connection                |
| ----------------- | ------------------------- |
| ESP32-CAM GPIO 12 | 1kΩ Resistor → BC547 Base |
| BC547 Emitter     | GND                       |
| BC547 Collector   | LED Negative (-)          |
| LED Positive (+)  | 330Ω Resistor → 5V        |

> ⚠️ **Important:** The exact BC547 pin arrangement can vary by manufacturer. Check the datasheet of your transistor before connecting it.

---

## 🧠 How It Works

The system operates in the following sequence:

```text
        👤 Person Detected
               │
               ▼
        🚶 PIR Sensor
               │
               ▼
       ESP32-CAM Detects Motion
               │
        ┌──────┴──────┐
        ▼             ▼
   📷 Capture      💡 Turn ON
     Image             LED
        │
        ▼
   📧 Send Email
   with Image
        │
        ▼
   🌐 Live Camera
   Web Page
```

### Step-by-step

1. The **PIR sensor** detects movement.
2. The PIR sensor sends a HIGH signal to **GPIO 13**.
3. The ESP32-CAM detects the motion.
4. The ESP32-CAM captures an image.
5. The captured image is sent to the configured email address.
6. The ESP32-CAM activates the **BC547 transistor**.
7. The LED turns ON as a motion indicator.
8. The camera can also be accessed through a web browser for live viewing.

---

## 💻 Software Requirements

* Arduino IDE
* ESP32 Board Package for Arduino IDE
* ESP32 Camera Library
* ESP Mail Client Library

### Required Libraries

```text
esp_camera.h
WiFi.h
ESP_Mail_Client.h
```

---

## ⚙️ Setup

### 1. Install Arduino IDE

Download and install the Arduino IDE.

### 2. Install ESP32 Board Support

Add ESP32 board support to the Arduino IDE and select the appropriate ESP32-CAM board.

### 3. Configure Wi-Fi

Update the following values in the code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 4. Configure Email

Set the sender and receiver email addresses:

```cpp
#define AUTHOR_EMAIL "yourmail@gmail.com"
#define AUTHOR_PASSWORD "YOUR_APP_PASSWORD"
#define RECIPIENT_EMAIL "receiver@gmail.com"
```

> ⚠️ For Gmail, use a **Google App Password** instead of your normal Gmail password.

### 5. Upload the Code

Connect the ESP32-CAM to your computer using a suitable USB-to-Serial programmer or ESP32-CAM programmer board.

Upload the code and open the Serial Monitor at:

```text
115200 baud
```

### 6. Access the Live Camera

After connecting to Wi-Fi, the ESP32-CAM will display its IP address in the Serial Monitor.

Open the IP address in a web browser:

```text
http://ESP32-CAM-IP
```

Example:

```text
http://192.168.1.100
```

You can then view the camera through the web interface.

---

## 📧 Email Alert

When the PIR sensor detects motion:

```text
Motion Detected
       ↓
Capture Image
       ↓
Attach Image to Email
       ↓
Send Email
```

The email contains the image captured by the ESP32-CAM.

---

## 🌐 Live Camera Streaming

The ESP32-CAM hosts a web server that allows the user to access the camera through a web browser.

The system can be used for:

* 🏠 Home security
* 🚪 Door monitoring
* 🏢 Office surveillance
* 📦 Package monitoring
* 🐾 Pet monitoring
* 🚨 Motion-based security alerts

---

## 🔒 Security Notes

* Do **not** upload your Wi-Fi password to GitHub.
* Do **not** upload your Gmail password or App Password.
* Use placeholders in public repositories.

Example:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

For email credentials, consider using a separate configuration file that is excluded from Git using `.gitignore`.

---

## ⚠️ Important Safety Notes

* Use a stable **5V power supply** for the ESP32-CAM.
* Do not connect an unregulated high-voltage supply directly to the ESP32-CAM.
* Always verify the **BC547 transistor pinout** before wiring.
* Use a resistor with the LED to limit current.
* Ensure that the ESP32-CAM, PIR sensor, and external power supply share a **common GND**.
* Check all connections before powering the circuit.

---

## 📁 Suggested Project Structure

```text
ESP32-CAM-Motion-Email-Alert/
│
├── ESP32-CAM-Motion-Email-Alert.ino
├── README.md
├── circuit-diagram.png
└── images/
    └── project.jpg
```

---

## 🔮 Future Improvements

Possible future upgrades include:

* 📱 Telegram notifications
* ☁️ Cloud image storage
* 👤 Human detection using AI
* 🎥 Video recording
* 💾 MicroSD card image storage
* 🔔 Buzzer alarm
* 📲 Mobile application
* 🌙 Night vision
* 🔐 Password-protected camera access
* 🧠 Face recognition

---

## 👨‍💻 Project

**Project Name:** ESP32-CAM Motion Detection & Email Alert System

**Platform:** ESP32-CAM

**Programming Language:** C/C++ (Arduino)

**Communication:** Wi-Fi

**Author:** Your Name

---

## ⭐ Support

If you find this project useful, consider giving the repository a ⭐ **Star** on GitHub!

Feel free to fork the project, experiment with it, and improve it.

---

## 📜 License

This project is open-source and available under the **MIT License**.
