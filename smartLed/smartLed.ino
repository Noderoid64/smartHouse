#include "logicModule.h"
#include "webModule.h"

#define AP_SSID "esp"
#define AP_PSWD "qwertyui"
#define SERIAL_SPEED 115200

WebModule webModule(true);

void setup() {
  Serial.begin(SERIAL_SPEED);
  webModule.createAccessPoint(AP_SSID, AP_PSWD);
  webModule.createWebServer();
}

void loop() {
 webModule.handleServer();
}
