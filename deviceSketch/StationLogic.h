#ifndef STATION_LOGIC_H
#define STATION_LOGIC_H

#include <ESP8266WebServer.h>
#include "webModule.h"
#include "DHT.h"

class LogicModule {
  public:
    LogicModule(bool isSerial);
    void init(WebModule* webModule);
  private:
    bool _isSerial;
    DHT *dht;
    void getHumidity(ESP8266WebServer*);
    void getTemperature(ESP8266WebServer*);
    void getAirQuality(ESP8266WebServer*);
};

#endif