
#define SKETCHVER "2022-11-23 01"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

const char* ssid = "starkhome";
const char* password = "starkenburg";

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // UN-init 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.println("Brownout Detector Disabled");



  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello! This is a simple text message sent from ESP32. Microcontrollerslab");
  });

  AsyncElegantOTA.begin(&server);    
  server.begin();
  Serial.println("HTTP server started!!");
  Serial.println(SKETCHVER);
  
}

void loop(void) {
  AsyncElegantOTA.loop();
}  