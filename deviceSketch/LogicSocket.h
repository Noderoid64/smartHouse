#ifndef LOGIC
#define LOGIC

#include <ESP8266WebServer.h>
#include <Arduino.h>
#include "Store.h";

class Logic {
  public:
  Logic(Store *store);
  void registerHandlers(ESP8266WebServer* server);
  private:
  void onTurnOn();
  void onTurnOff();
  void onGetStatus();
};


#endif
