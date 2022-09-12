#include <Arduino.h>
#include <WiFi.h>
#include <math.h>
#include "ArduinoJson.h"

const char* ssid = "hotspot-Blain";
const char* pwd = "hotspot123";
int status = WL_IDLE_STATUS;

WiFiServer wifiServer;
WiFiClient client;
unsigned char buf[sizeof(double)];

double getWifiIntensity();


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pwd);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nConnected to the WiFi network");
  Serial.println(WiFi.localIP());
  wifiServer.begin(80);
}

void loop() {
  client = wifiServer.available();
  if(client){
      Serial.print("Client connected with IP:");
      Serial.println(client.remoteIP());
      while(client.connected()){
        // if(client.available()){
          double signal = getWifiIntensity();
          memcpy(buf, &signal, sizeof(double));
          client.write(buf, sizeof(double));
          delay(200);
        // }
      }
      
  } else {
      Serial.println("Client not connected");
      delay(1000);
  }
    // if(WiFi.status() != WL_CONNECTED){
    //     WiFi.begin(ssid, pwd);
    //     while (WiFi.status() != WL_CONNECTED) {
    //         delay(1000);
    //         Serial.println("Connecting to WiFi..");
    //     }
    //     Serial.println("Connected to the WiFi network");
    //     Serial.println(WiFi.localIP());
    // }

}

double getWifiIntensity() {
  int8_t rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  double rssi_lin = log10(abs(rssi)) * 20;
  // Serial.print("log10(RSSI): ");
  // Serial.print(log10(abs(rssi)));
  Serial.println(rssi_lin);
  return rssi_lin;
}