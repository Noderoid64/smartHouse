#ifndef UDP_MODULE
#define UDP_MODULE

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class UdpModule {
  public: 
  UdpModule();
  void handleUDP(String type, String version);
  void sendUdp(String ip, String message);
  private:
  
  WiFiUDP* udpClient = new WiFiUDP();
  IPAddress* multicastAddress;
};


#endif
