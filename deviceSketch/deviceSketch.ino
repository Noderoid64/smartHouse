#include "webModule.h"
#include "logicModule.h"
#include "commonModule.h"

#define SERIAL_SPEED 115200
#define TYPE "SOCKET"
#define VERSION "0.1.5"

LogicModule logicModule(true, VERSION, TYPE);
CommonModule commonModule;
WebModule webModule(true, &commonModule);

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Start");
  webModule.init();
  logicModule.init(&webModule);
  webModule.createWebServer();
  
}

void loop() {
 webModule.handleServer((String)TYPE,(String) VERSION); 
}
