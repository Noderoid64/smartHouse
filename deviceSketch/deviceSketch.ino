#include "StationLogic.h"
#include "webModule.h"
#include "Async.h"
#include "storageModule.h"
#include "NetModule.h"
#include "System.h"

#define SERIAL_SPEED 115200
#define TYPE "SOCKET"
#define VERSION "0.1.5"

LogicModule logicModule(true);
StorageModule storageModule (VERSION, TYPE);
NetModule netModule(&storageModule);
WebModule webModule(&netModule, &storageModule);
System csystem(&netModule, &storageModule);

void setup() {
  Serial.begin(115200);
  storageModule.ClearAll();
  csystem.tryConnectToLastNet([&] () {
    csystem.createAP();  
  });
  webModule.startWebServer();
  logicModule.init(&webModule);
  
}


void loop() {
  asyncTick();
  webModule.handleServer();
  
}
