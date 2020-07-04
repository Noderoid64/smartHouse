#include <ESP8266WebServer.h>
#include <FS.h>
#include "webModule.h"
#include "storageModule.h"

// Constants
#define AP_PAGE_PATH "/ap.html"
#define WS_PAGE_PATH "/ws.html"
#define MESSAGE_PAGE_PATH "/message.html"
#define ERROR_PAGE_PATH "/error.html"
#define LOADING_PAGE_PATH "/loading.html"

#define APPLICATION_JSON_TYPE "application/json"
#define HTML_CONTENT_TYPE "text/html"
#define CSS_CONTENT_TYPE "text/css"
#define JS_CONTENT_TYPE "application/javascript"
#define ICON_CONTENT_TYPE "image/x-icon"

WebModule::WebModule(NetModule *_netModule, StorageModule *_storageModule) {
  netModule = _netModule;
  storageModule = _storageModule;
  server = new ESP8266WebServer(80);
}

void WebModule::startWebServer() {
  server->on("/main", [ = ] () -> void {onMain();});
  server->on("/disconnect", [ = ] () -> void {onDisconnect();});
  server->on("/login", [ = ] () -> void {onLogin();});
  server->on("/info", [ = ] () -> void {onInfo();});
  server->onNotFound([ = ] () -> void {onNotFound();});
  server->begin();
}

void WebModule::stopWebServer() {
  server->stop();
}

void WebModule::registerHandler(char* route, std::function<void(ESP8266WebServer*)> handler) {
  server->on(route, [ = ] () -> void {handler(server);});
}

void WebModule::handleServer() {
  server->handleClient();
}

void WebModule::onMain() {
  if (storageModule->getIsWS() == true) {
    String response = getFileAsString(WS_PAGE_PATH);
    response.replace("{{ssid}}", storageModule->getSsid());
    server->send(200, HTML_CONTENT_TYPE, response);
  } else {
    if (storageModule->getIsAP() == true) {
      String response = getFileAsString(AP_PAGE_PATH);
      server->send(200, HTML_CONTENT_TYPE, response);
    } else {
      server->send(404, "text/plain");
    }
  }
}

void WebModule::onLogin() {
  String response;
  if (server->hasArg("ssid") && server->arg("ssid") != "") {
    if (server->hasArg("pass") && server->arg("pass") != "") {
      String ssid = server->arg("ssid");
      String pass = server->arg("pass");
      netModule->connectToWifi(ssid, pass, 
        [&]() {
          server->send(200, APPLICATION_JSON_TYPE, "No");
        },
        [&]() {
          storageModule->setSsid(ssid);
          storageModule->setPass(pass);
          server->send(200, APPLICATION_JSON_TYPE, "Yes");
        }
      );
    } else {
      server->send(200, APPLICATION_JSON_TYPE, "passwod empty");
    }
  } else {
    server->send(200, APPLICATION_JSON_TYPE, "ssid empty");
  }
}

void WebModule::onDisconnect() {
  netModule->disconnectFromWifi(
    [&]() {
      storageModule->setSsid("");
      storageModule->setPass("");
    }
  );
}

void WebModule::onInfo() {
  String result = 
  storageModule->getVersion() + "|" +
  storageModule->getType() + "|" +
  storageModule->getSsid() + "|" +
  storageModule->getIsAP() + "|" +
  storageModule->getIsWS();
  
  server->send(200, APPLICATION_JSON_TYPE, result);
}

void WebModule::onNotFound() {
  if (!onFileHandler(server->uri())) {
    server->sendHeader("Location", "/main");
    server->send(303);
  }
}

bool WebModule::onFileHandler(String url) {
  String contentType = getContentType(url);
  if (contentType != "") {
    if (SPIFFS.exists(url)) {
      File file = SPIFFS.open(url, "r");                 // Open it
      size_t sent = server->streamFile(file, contentType); // And send it to the client
      file.close();
    }
  } else {
    return false;
  }
}

String WebModule::getFileAsString(String path) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    return file.readString();
  }
}

String WebModule::getContentType(String filename) {
  if (filename.endsWith(".html")) return HTML_CONTENT_TYPE;
  else if (filename.endsWith(".css")) return CSS_CONTENT_TYPE;
  else if (filename.endsWith(".js")) return JS_CONTENT_TYPE;
  else if (filename.endsWith(".ico")) return ICON_CONTENT_TYPE;
  return "";
}
