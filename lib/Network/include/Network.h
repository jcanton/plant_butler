#include <WiFiS3.h>
#include <map>

class NetworkClient {
    WiFiClient client;
    const char* WIFI_SSID;
    const char* WIFI_PASS;
    const char* HOST_NAME;
    uint16_t HTTP_PORT;

public:
    NetworkClient(const char* ssid, const char* pass);
    void connectWiFi();
    void printWiFiStatus();

    void connectToServer(const char* host, uint16_t port);
    bool connectedToServer();
    void sendData(std::map<std::string, float>);
    void getServerReply();
};