/*###
    Logic Module v1.0.0
  ###*/

#ifndef LOGIC_MODULE_H
#define LOGIC_MODULE_H

#include <ESP8266WebServer.h>
#include "webModule.h"

class LogicModule {
  public:
    LogicModule(bool isSerial, String deviceVersion, String deviceType);
    void init(WebModule* webModule);
  private:
    bool _isSerial;
    String _deviceVersion;
    String _deviceType;
    bool pinStatus;
    void handleTurnOn(ESP8266WebServer*);
    void handleTurnOff(ESP8266WebServer*);
    void handleGetStatus(ESP8266WebServer*);
    void handleInfo(ESP8266WebServer*);
};

#endif
