#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "webModule.h"

// Constants
#define LOGIN_PAGE_PATH "/main.html"
#define MESSAGE_PAGE_PATH "/message.html"
#define ERROR_PAGE_PATH "/error.html"
#define HTML_CONTENT_TYPE "text/html"
#define CSS_CONTENT_TYPE "text/css"
#define JS_CONTENT_TYPE "application/javascript"
#define CONNECTION_TIMEOUT 7000

// Funciton implementation
WebModule::WebModule(bool isSerial) {
  server = new ESP8266WebServer(80);
  _isSerial = isSerial;
  if (_isSerial) {
    Serial.println("webModule is initialized:");
    Serial.println("isSerial: " + _isSerial);
  }
}

void WebModule::createAccessPoint(String ssid, String password) {
  if (_isSerial) {
    Serial.println("start AP on \n ssid: " + ssid + "\n pass: " + password );
  }
  WiFi.softAP(ssid, password);
  _isAP = true;
  if (_isSerial) {
    Serial.print("ip address: ");
    Serial.println( WiFi.softAPIP());
  }
}

void WebModule::createWorkStation(String ssid, String password) {
  if (_isSerial) {
    Serial.println("start WS on \n ssid: " + ssid + "\n pass: " + password );
  }
  long startTime = millis();
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(200);
    if(millis() - startTime >= CONNECTION_TIMEOUT) {
      if(_isSerial) {
        Serial.println("connection timeout");
        return;
      }
    }
  }
  _isWS = true;
  if (_isSerial) {
    Serial.println("connected");
    Serial.print("local ip address: ");
    Serial.println( WiFi.localIP());
  }
}

void WebModule::destroyAccessPoint() {
  bool isDisconnected = WiFi.softAPdisconnect();
  if(_isSerial) {
    Serial.println("destroyAP: " + isDisconnected);
  }
}

void WebModule::createWebServer() {
  SPIFFS.begin();
  if (_isSerial) {
    Serial.println("started SPIFFS");
  }
  server->on("/main", [ = ] () -> void {onMainHandler();});
  server->on("/login", [ = ] () -> void {onLoginHandler();});
  server->onNotFound([ = ] () -> void {onNotFoundHandler();});
  server->begin();
  if (_isSerial) {
    Serial.println("started WebServer");
  }
}

void WebModule::registerHandler(char* route, std::function<void(ESP8266WebServer*)> handler) {
  server->on(route, [ = ] () -> void {handler(server);});
}

void WebModule::onLoginHandler() {
  String response;
  if (server->hasArg("ssid") && server->arg("ssid") != "") {
    if (server->hasArg("pass") && server->arg("pass") != "") {
      response = getFileAsString(MESSAGE_PAGE_PATH);
      response.replace("{{message}}", "Connecting... press 'Back to menu' after a few seconds ");
      server->send(200, HTML_CONTENT_TYPE, response);
      createWorkStation(server->arg("ssid"), server->arg("pass"));
    } else {
      if (_isSerial) {
        Serial.println("onLoginHandler: pass not found");
      }
      response = getFileAsString(ERROR_PAGE_PATH);
      response.replace("{{error}}", "Password is empty");
      server->send(200, HTML_CONTENT_TYPE, response);
    }
  } else {
    if (_isSerial) {
      Serial.println("onLoginHandler: ssid not found");
    }
    response = getFileAsString(ERROR_PAGE_PATH);
    response.replace("{{error}}", "SSID is empty");
    server->send(200, HTML_CONTENT_TYPE, response);
  }

}

void WebModule::onNotFoundHandler() {
  if (_isSerial) {
    Serial.println("redirect from " + server->uri() + " to /main");
  }
  server->sendHeader("Location", "/main");
  server->send(303);
}

void WebModule::onMainHandler() {
  if (_isSerial) {
    Serial.print("request");
  }
  if (_isAP == true) {
    sendFile((char*)LOGIN_PAGE_PATH);
  } else {
    server->send(404, "text/plain");
    if (_isSerial) {
      Serial.println("sever sent 404");
    }
  }
}

void WebModule::handleServer() {
    server->handleClient();
}

void WebModule::sendFile(String path) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server->streamFile(file, HTML_CONTENT_TYPE); // And send it to the client
    file.close();
    if (_isSerial) {
      Serial.print("file returned: ");
      Serial.println(path);
    }
  } else {
    if (_isSerial) {
      Serial.print("file not fould in ");
      Serial.println(path);
    }
  }
}

String WebModule::getFileAsString(String path) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    return file.readString();
  } else {
    if (_isSerial) {
      Serial.println("file not found in " + path);
    }
  }
}
