#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include "SSD1306Wire.h"
#include "Dialog12.h"

#define SDA 10
#define SCL 9

SSD1306Wire display(0x3c, SDA, SCL);
WiFiServer server(80);

String wifi_ip = "";

void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(Dialog_plain_12);
  display.clear();

  WiFi.mode(WIFI_STA);
  WiFi.begin("gabin", "1110012814");
  display.drawString(0, 0, "WiFi Connecting");
  display.display();
  int i = 0;

  while (WiFi.status() != WL_CONNECTED) {
    display.drawString(i, 15, ".");
    display.display();
    delay(500);
    i += 8;
  }
  wifi_ip = WiFi.localIP().toString();
  display.drawString(0, 30, "IP: "+wifi_ip);

  server.begin();
  display.drawString(0, 45, "Webserver started.");  
  display.display();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buffer[50];
  int i = 0;
  while(i < 256) {
    analogWrite(D4, 255-i);
    analogWrite(D0, i);
    display.clear();
    display.drawString(0, 0, "IP: "+wifi_ip);
    display.drawStringf(0, 15, buffer, "Bright: %.1f%%", i/255.0*100);
    display.display();
    i++;
    delay(10);
  }
  delay(2000);
  while(i >=0) {
    analogWrite(D4, 255-i);
    analogWrite(D0, i);
    display.clear();
    display.drawString(0, 0,"IP: "+wifi_ip);
    display.drawStringf(0, 15, buffer, "Bright: %.1f%%", i/255.0*100);
    display.display();
    i--;
    delay(10);
  }
  delay(2000);

}