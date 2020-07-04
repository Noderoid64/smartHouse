/*###
    Net Module v1.0.0
  ###*/

#ifndef NET_MODULE_H
#define NET_MODULE_H

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "storageModule.h"

class NetModule {
  public:
    NetModule(StorageModule *_storageModule);
    void startAP(String ssid, String password);
    void stopAP();
    void connectToWifi(String ssid, String password, std::function<void()> onError, std::function<void()> onSuccess);
    void disconnectFromWifi(std::function<void()> func);
    void sendUdpBroadcast(String message);
  private:
    StorageModule *storageModule;
    WiFiUDP *udp;
    IPAddress *multicastAddress;
};

#endif
