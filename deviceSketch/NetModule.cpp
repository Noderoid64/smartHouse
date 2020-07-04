#include "NetModule.h"

#define CONNECTION_TIMEOUT 12000
#define MULTICAST_PORT 4446

NetModule::NetModule(StorageModule *_storageModule) {
  multicastAddress = new IPAddress(230,0,0,0);
  udp = new WiFiUDP();
  storageModule = _storageModule;
}

void NetModule::startAP (String ssid, String password) {
  WiFi.softAP(ssid, password);
  storageModule->setIsAP(true);
}

void NetModule::stopAP() {
  WiFi.softAPdisconnect();
  storageModule->setIsAP(false);
}

void NetModule::connectToWifi(String ssid, String password, std::function<void()> onError, std::function<void()> onSuccess) {
  long startTime = millis();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    if (millis() - startTime >= CONNECTION_TIMEOUT) {
      storageModule->setIsWS(false);
      onError();
      return;
    }
  }
  Serial.println(WiFi.localIP());
  storageModule->setIsWS(true);
  onSuccess();
}

void NetModule::disconnectFromWifi(std::function<void()> func) {
  WiFi.disconnect();
  func();
}

void NetModule::sendUdpBroadcast (String message) {
  char msg[255];
    message.toCharArray(msg,255);
    udp->beginPacketMulticast(*multicastAddress, MULTICAST_PORT, WiFi.localIP());
    udp->write(msg);
    udp->endPacket();
}
