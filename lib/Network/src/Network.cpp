#include "Network.h"

char buffer[10];
String server_reply;

NetworkClient::NetworkClient(const char* ssid, const char* pass) : wifi_ssid(ssid), wifi_pass(pass) {}

void NetworkClient::connectWiFi()
{
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    Serial.println("WiFi firmware version: " + String(WiFi.firmwareVersion()) + " / " + String(WIFI_FIRMWARE_LATEST_VERSION));

    WiFi.begin(wifi_ssid, wifi_pass);
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
    host_name = host;
    http_port = port;

    if(client.connect(host_name, http_port)) {
        Serial.print("Connected to server " + String(host_name) + " ");
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
    char query_string[99];

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

    strcpy(query_string, "?potnr=");
    strcat(query_string, std::to_string(int(data["potnr"])).c_str());
    data.erase("potnr");

    for (const auto &pair : data) {
        // Do something with key and value
        strcat(query_string, "&");
        strcat(query_string, pair.first.c_str());
        strcat(query_string, "=");
        sprintf(buffer, "%.2f", pair.second);
        strcat(query_string, buffer);
    }

    client.println("GET  /test/arduino_landing.php" + String(query_string) + " HTTP/1.1");
    client.println("Host: " + String(host_name));
    client.println("Connection: close");
    client.println(); // end HTTP header

    Serial.println("Sent data: " + String(query_string));
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
        server_reply += client.readString();
    }
    if (server_reply.length() > 0) {
        Serial.println();
        Serial.println("--------------Answer from server:-------------");
        Serial.println();
        Serial.print(server_reply);
        Serial.println();
        Serial.println("----------End of Answer from server.----------");
        Serial.println();
    }
    server_reply="";
}
