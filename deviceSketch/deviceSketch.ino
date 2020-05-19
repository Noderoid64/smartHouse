#include "webModule.h"
#include "logicModule.h"

#define AP_SSID "esp"
#define AP_PSWD "qwertyui"
#define SERIAL_SPEED 115200
#define TYPE "SOCKET"
#define VERSION "0.1.5"

WebModule webModule(true);
LogicModule logicModule(true, VERSION, TYPE);

void setup() {
  Serial.begin(SERIAL_SPEED);
  webModule.createAccessPoint(AP_SSID, AP_PSWD);
  logicModule.init(&webModule);
  webModule.createWebServer();
  
}

void loop() {
 webModule.handleServer((String)TYPE,(String) VERSION);
}
