/*###
    Web Module v0.1.0
  ###*/

#ifndef WEB_MODULE_H
#define WEB_MODULE_H

#include <ESP8266WebServer.h>
#include "netModule.h"
#include "storageModule.h"

class WebModule {
  public:
    WebModule(NetModule *_netModule, StorageModule *_storageModule);
    void startWebServer();
    void stopWebServer();
    void registerHandler(char* route, std::function<void(ESP8266WebServer*)> handler);
    void handleServer();
  private:
    ESP8266WebServer *server;
    NetModule *netModule;
    StorageModule *storageModule;
    void onMain();
    void onLogin();
    void onDisconnect();
    void onInfo();
    void onNotFound();
    bool onFileHandler(String url);
    String getFileAsString(String path);
    String getContentType(String filename);
    

};
#endif
