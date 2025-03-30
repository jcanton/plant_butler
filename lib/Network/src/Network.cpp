#include "Network.h"

char buffer[10];
String serverReply;

NetworkClient::NetworkClient(const char* ssid, const char* pass) : WIFI_SSID(ssid), WIFI_PASS(pass) {}

void NetworkClient::connectWiFi()
{
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    Serial.println("WiFi firmware version: " + String(WiFi.firmwareVersion()) + " / " + String(WIFI_FIRMWARE_LATEST_VERSION));

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Connecting to Wi-Fi.");
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(300);
    }
    printWiFiStatus();
}

void NetworkClient::printWiFiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your board's IP address:
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // print the received signal strength:
    Serial.print("signal strength (RSSI):");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}

void NetworkClient::connectToServer(const char* host, uint16_t port)
{
    HOST_NAME = host;
    HTTP_PORT = port;

    if(client.connect(HOST_NAME, HTTP_PORT)) {
        Serial.print("Connected to server " + String(HOST_NAME) + " ");
        Serial.println(client.remoteIP());
    } else {
        Serial.println("Failed to connect");
    }
}

bool NetworkClient::connectedToServer()
{
    return client.connected();
}

void NetworkClient::sendData(std::map<std::string, float> data)
{
    char queryString[99];

    auto it = data.find("potnr");
    if (it == data.end()) {
        // The key does not exist
        Serial.println("Key 'potnr' not found in data map");
        return;
    }

    if (!connectedToServer()) {
        Serial.println("Server not connected, could not send data");
        return;
    }

    Serial.println("Sending data...");

    strcpy(queryString, "?potnr=");
    strcat(queryString, std::to_string(int(data["potnr"])).c_str());
    data.erase("potnr");

    for (const auto &pair : data) {
        // Do something with key and value
        strcat(queryString, "&");
        strcat(queryString, pair.first.c_str());
        strcat(queryString, "=");
        sprintf(buffer, "%.2f", pair.second);
        strcat(queryString, buffer);
    }

    client.println("GET  /test/arduino_landing.php" + String(queryString) + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header

    Serial.println("Sent data: " + String(queryString));
}

void NetworkClient::getServerReply()
{
    // If there are incoming bytes available from the server, read and print
    // them:
    Serial.print("Waiting for data from server.");
    while(client.connected() && !client.available()) {
        delay(1);
        Serial.print(".");
    }
    Serial.println();
    while (client.connected() || client.available()) { //connected or data available
        serverReply += client.readString();
    }
    if (serverReply.length() > 0) {
        Serial.println();
        Serial.println("--------------Answer from server:-------------");
        Serial.println();
        Serial.print(serverReply);
        Serial.println();
        Serial.println("----------End of Answer from server.----------");
        Serial.println();
    }
    serverReply="";
}
