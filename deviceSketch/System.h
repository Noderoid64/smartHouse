#ifndef SYSTEM_H
#define SYSTEM_H

#include "webModule.h"
#include "netModule.h"
#include "storageModule.h"

class System {
  public:
    System(NetModule *_netModule, StorageModule *_storageModule);
    void tryConnectToLastNet(std::function<void()> onError);
    void createAP();
  private:
  NetModule *netModule;
  StorageModule *storageModule;
};

#endif
