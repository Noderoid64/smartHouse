#include "webModule.h"
#include "NetModule.h"
#include "storageModule.h"

#include "System.h"

#define SSID "NodSocket"
#define PASS "12345678"

System::System(NetModule *_netModule, StorageModule *_storageModule) {
  netModule = _netModule;
  storageModule = _storageModule;
}

void System::tryConnectToLastNet(std::function<void()> onError) {
  String ssid = storageModule->getSsid();
  String pass = storageModule->getPass();
  if (ssid != "" && pass != "") {
    netModule->connectToWifi(ssid, pass,
      [&] () {
        onError();
      },
      [&] () {}
    );
    } else {
      onError();
  }
}

void System::createAP() {
  netModule->startAP(SSID, PASS);
}
    
