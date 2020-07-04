#ifndef STORAGE_MODULE_H
#define STORAGE_MODULE_H

#include <FS.h>

class StorageModule {
  public:
    StorageModule(String version, String type);
    void ClearAll();
    // SSID
    String getSsid();
    void setSsid(String ssid);
    // PASS
    String getPass();
    void setPass(String pass);
    // isWS
    bool getIsWS();
    void setIsWS(bool value);
    // isAP
    bool getIsAP();
    void setIsAP(bool value);
    // Type
    String getType();
    void setType(String value);
    // Version
    String getVersion();
    void setVersion(String value);
    
  private:
    void proxyInput(int param, String value);
    String proxyOutput(int param);
};

#endif
