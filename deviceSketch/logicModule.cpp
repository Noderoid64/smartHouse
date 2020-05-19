#include "logicModule.h"
#include <ESP8266WebServer.h>

#define OUTPUT_PIN 0
#define APPLICATION_JSON_TYPE "application/json"

LogicModule::LogicModule(bool isSerial, String deviceVersion, String deviceType) {
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  _isSerial = isSerial;
  pinStatus = false;
  _deviceVersion = deviceVersion;
  _deviceType = deviceType;
}

void LogicModule::init(WebModule* webModule) {
    webModule->registerHandler("/on",[=] (ESP8266WebServer* server) {handleTurnOn(server);});
    webModule->registerHandler("/off", [=] (ESP8266WebServer* server) {handleTurnOff(server);});
    webModule->registerHandler("/status", [=] (ESP8266WebServer* server) {handleGetStatus(server);});
    webModule->registerHandler("/info", [=] (ESP8266WebServer* server) {handleInfo(server);});
}

void LogicModule::handleTurnOn(ESP8266WebServer* server) {
  if(_isSerial) {
    Serial.println("Turn On");
  }
  pinStatus = true;
  digitalWrite(OUTPUT_PIN, HIGH);
  server->send(200, APPLICATION_JSON_TYPE, "Turn on");
}

void LogicModule::handleTurnOff(ESP8266WebServer* server){
  if(_isSerial) {
    Serial.println("Turn Off");
  }
  pinStatus = false;
  digitalWrite(OUTPUT_PIN, LOW);
  server->send(200, APPLICATION_JSON_TYPE, "Turn off");
}

void LogicModule::handleGetStatus(ESP8266WebServer* server){
  if(_isSerial) {
    Serial.println("Get status");
  }
  server->send(200, APPLICATION_JSON_TYPE, pinStatus ? "HIGHT" : "LOW");
}

void LogicModule::handleInfo(ESP8266WebServer* server) {
  if(_isSerial) {
    Serial.println("Return info");
  }
  String result = _deviceVersion + "|" + _deviceType;
  server->send(200, APPLICATION_JSON_TYPE, result);
}
