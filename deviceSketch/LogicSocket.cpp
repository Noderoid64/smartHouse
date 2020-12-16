#include "LogicSocket.h"
#include "Store.h"

#define SOCKET_PIN 2

ESP8266WebServer* lserver;
Store *lstore;

Logic::Logic(Store* _store) {
  lstore = _store;
}

void Logic::registerHandlers (ESP8266WebServer* _server) {
  lserver = _server;
  lserver->on("/on", [&](){this->onTurnOn();});
  lserver->on("/off", [&](){this->onTurnOff();});
  lserver->on("/status", [&](){this->onGetStatus();});

  pinMode(SOCKET_PIN, OUTPUT);

  bool status = lstore->getBool(S_FREE) == true;
  if (status) {
    digitalWrite(SOCKET_PIN, HIGH);
  } else {
    digitalWrite(SOCKET_PIN, LOW);
  }
  
}

void Logic::onTurnOn() {
  #ifdef EN_SER
  Serial.println("onTurnOn start");
  #endif 
  digitalWrite(SOCKET_PIN, HIGH);
  lserver-> send(200, "text/plain", "turned on");
  lstore->setBool(true, S_FREE);
}

void Logic::onTurnOff() {
  #ifdef EN_SER
  Serial.println("onTurnOff start");
  #endif
  digitalWrite(SOCKET_PIN, LOW);
  lserver-> send(200, "text/plain", "turned off");
  lstore->setBool(false, S_FREE);
}

void Logic::onGetStatus() {
  #ifdef EN_SER
  Serial.println("onGetStatus start");
  #endif
  bool status = lstore->getBool(S_FREE) == true;
  String result = "status: ";
  if (status) {
    result = result + "on";
  } else {
    result = result + "off";
  }
  lserver->send(200, "text/plain", result);
}
