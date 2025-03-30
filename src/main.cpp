#include <Arduino.h>

#include <WiFiS3.h>
#include <Network.h>

#include <constants.h>
#include <secrets.h>

NetworkClient netcli(WIFI_SSID, WIFI_PASS);

#include <map>

std::map<std::string, float> data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n\nStarting up...");

  netcli.connectWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
  Serial.println("\n\n==========================================================================");

  netcli.connectToServer(HOST_NAME, HTTP_PORT);

  // Add a key-value pair to the map
  data["potnr"] = 3;
  data["temp"] = 21.2;
  data["humi"] = 83;
  // Transmit data to web server
  netcli.sendData(data);
  netcli.getServerReply();

}