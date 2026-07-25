#include "esp_camera.h"
#include <WiFi.h>
#include <ESP_Mail_Client.h>

// WiFi
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// Email
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "yourmail@gmail.com"
#define AUTHOR_PASSWORD "your_app_password"
#define RECIPIENT_EMAIL "receiver@gmail.com"

SMTPSession smtp;

// PIR
#define PIR_PIN 13

bool motionDetected = false;

// Camera config (AI Thinker ESP32-CAM)
void startCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sccb_sda = 26;
  config.pin_sccb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  esp_camera_init(&config);
}

// Send Email with Image
void sendPhoto() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  SMTP_Message message;

  message.sender.name = "ESP32-CAM";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Motion Detected!";
  message.addRecipient("User", RECIPIENT_EMAIL);

  message.text.content = "Motion detected. Image attached.";

  SMTP_Attachment att;
  att.descr.filename = "image.jpg";
  att.blob.data = fb->buf;
  att.blob.size = fb->len;
  att.descr.mime = "image/jpeg";

  message.addAttachment(att);

  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  if (!smtp.connect(&session)) {
    Serial.println("SMTP connect failed");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Error sending Email");
  } else {
    Serial.println("Email sent!");
  }

  esp_camera_fb_return(fb);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");

  pinMode(PIR_PIN, INPUT);

  startCamera();
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    if (!motionDetected) {
      Serial.println("Motion detected!");

      sendPhoto();   // 📧 send email

      motionDetected = true;
      delay(10000);  // avoid spam
    }
  } else {
    motionDetected = false;
  }
}