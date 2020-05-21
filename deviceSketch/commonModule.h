/*###
    Logic Module v1.0.0
  ###*/

#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

#include <FS.h>

class CommonModule {
  public:
    CommonModule();
    // SSID
    String getSsid();
    void setSsid(String ssid);
    // PASS
    String getPass();
    void setPass(String pass);
    
  private:
    void proxyInput(int param, String value);
    String proxyOutput(int param);
};

#endif
