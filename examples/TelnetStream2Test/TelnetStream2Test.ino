#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <ArduinoOTA.h>
#include <WiFiManager.h>
#include <TelnetStream2.h>

void setup() {
  Serial.begin(115200);
  ArduinoOTA.begin();

  WiFiManager wifiManager;
  wifiManager.autoConnect();

  TelnetStream2.begin();
}

void loop() {
  ArduinoOTA.handle();

  switch (TelnetStream2.read()) {
    case 'R':
    TelnetStream2.stop();
    delay(100);
    ESP.reset();
      break;
    case 'C':
      TelnetStream2.println("bye bye");
      TelnetStream2.flush();
      TelnetStream2.stop();
      break;
  }

  static unsigned long next = millis();
  if (millis() > next) {
    next += 5000;
    log();
  }
}

void log() {
  static int i = 0;
  TelnetStream2.print(i++);
  TelnetStream2.print(" ");
  TelnetStream2.print("Uptime: ");
  TelnetStream2.print(millis());
}
