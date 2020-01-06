/*###
    Web Module v0.1.0
  ###*/

#ifndef WEB_MODULE_H
#define WEB_MODULE_H

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
    void handleServer();
  private:
    void sendFile(String path);
    String getFileAsString(String path);
    bool _isSerial;
    bool _isAP;
    bool _isWS;

};
#endif
