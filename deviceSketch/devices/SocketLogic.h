#ifndef SOCKET_LOGIC_H
#define SOCKET_LOGIC_H

#include <ESP8266WebServer.h>
#include "webModule.h"

class LogicModule {
  public:
    LogicModule(bool isSerial);
    void init(WebModule* webModule);
  private:
    bool _isSerial;
    bool pinStatus;
    void handleTurnOn(ESP8266WebServer*);
    void handleTurnOff(ESP8266WebServer*);
    void handleGetStatus(ESP8266WebServer*);
};

#endif