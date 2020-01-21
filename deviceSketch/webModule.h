/*###
    Web Module v0.1.0
  ###*/

#ifndef WEB_MODULE_H
#define WEB_MODULE_H

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WebModule {
  public:
    ESP8266WebServer *server;

    WebModule(bool isSerial);
    void createAccessPoint(String ssid, String password);
    void createWorkStation(String ssid, String password);
    void destroyAccessPoint();
    void createWebServer();
    void registerHandler(char* route, std::function<void(ESP8266WebServer*)> handler);
    void onNotFoundHandler();
    void onMainHandler();
    void onLoginHandler();
    void onDisconnect();
    void handleServer(String type, String ver);
  private:
    WiFiUDP *udp;
    IPAddress *multicastAddress;
    void sendFile(String path, String contentType);
    void sendGreeting(String mac, String type, String vers);
    String getFileAsString(String path);
    bool onFileHandler(String url);
    void redirectToMain();
    String getContentType(String filename);
    bool _isSerial;
    bool _isAP;
    bool _isWS;
    String _networkSsid;
    String _errorMessage;
    long lastGreetingTime;

};
#endif
