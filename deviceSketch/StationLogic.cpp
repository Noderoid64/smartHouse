#include "StationLogic.h"
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHT_PIN 13
#define DHT_TYPE DHT11
#define AIR_QUALITY_PIN A0
#define APPLICATION_JSON_TYPE "application/json"

LogicModule::LogicModule(bool isSerial) {
  pinMode(AIR_QUALITY_PIN, INPUT);
  dht = new DHT(DHT_PIN, DHT_TYPE);
}

void LogicModule::init(WebModule* webModule) {
    webModule->registerHandler("/getHumidity",[=] (ESP8266WebServer* server) {getHumidity(server);});
    webModule->registerHandler("/getTemperature", [=] (ESP8266WebServer* server) {getTemperature(server);});
    webModule->registerHandler("/getAirQuality", [=] (ESP8266WebServer* server) {getAirQuality(server);});
    dht->begin();
}

void LogicModule::getHumidity(ESP8266WebServer* server) {
  float h = dht->readHumidity();
  server->send(200, APPLICATION_JSON_TYPE, String(h));
}

void LogicModule::getTemperature(ESP8266WebServer* server){
  float t = dht->computeHeatIndex(dht->readTemperature(), dht->readHumidity(), false);
  Serial.println(t);
  server->send(200, APPLICATION_JSON_TYPE, String(t));
}

void LogicModule::getAirQuality(ESP8266WebServer* server){

  server->send(200, APPLICATION_JSON_TYPE, String(analogRead(AIR_QUALITY_PIN)));
}
