#ifndef NETWORK_H
#define NETWORK_H

#include <WiFiS3.h>
#include <map>

class NetworkClient {
    WiFiClient client;
    const char* wifi_ssid;
    const char* wifi_pass;
    const char* host_name;
    uint16_t http_port;

public:
    NetworkClient(const char* ssid, const char* pass);
    void connectWiFi();
    void printWiFiStatus();
    void connectToServer(const char* host, uint16_t port);
    bool connectedToServer();
    void sendData(std::map<std::string, float> data);
    void getServerReply();
};

#endif // NETWORK_H