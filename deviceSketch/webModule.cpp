#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <FS.h>
#include "webModule.h"

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
#define CONNECTION_TIMEOUT 12000
#define MULTICAST_PORT 4446

// Funciton implementation
WebModule::WebModule(bool isSerial) {
  server = new ESP8266WebServer(80);
  multicastAddress = new IPAddress(230,0,0,0);
  udp = new WiFiUDP();
  _isSerial = isSerial;
  _pingTime = 5000;
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

bool WebModule::createWorkStation(String ssid, String password) {
  if (_isSerial) {
    Serial.println("start WS on \n ssid: " + ssid + "\n pass: " + password );
  }
  long startTime = millis();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    if (millis() - startTime >= CONNECTION_TIMEOUT) {
      _errorMessage = "Can't connect to network";
      if (_isSerial) {       
        Serial.println("connection timeout");
      }
      return false;
    }
  }
  _isWS = true;
  _networkSsid = ssid;
  if (_isSerial) {
    Serial.println("connected");
    Serial.print("local ip address: ");
    Serial.println( WiFi.localIP());
  }
  return true;
}

void WebModule::destroyAccessPoint() {
  bool isDisconnected = WiFi.softAPdisconnect();
  if (_isSerial) {
    Serial.println("destroyAP: " + isDisconnected);
  }
}

void WebModule::createWebServer() {
  SPIFFS.begin();
  if (_isSerial) {
    Serial.println("started SPIFFS");
  }
  server->on("/main", [ = ] () -> void {onMainHandler();});
  server->on("/disconnect", [ = ] () -> void {onDisconnect();});
  server->on("/login", [ = ] () -> void {onLoginHandler();});
  server->on("/network-info", [ = ] () -> void {onGetNetworkInfo();});
  server->on("/ping/get", [ = ] () -> void {onGetPingTime();});
  server->on("/ping/set", [ = ] () -> void {onSetPingTime();});
  server->on("/server/get", [ = ] () -> void {onGetServerIp();});
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
      if (createWorkStation(server->arg("ssid"), server->arg("pass")) == true) {
        server->send(200, APPLICATION_JSON_TYPE, "Ok");  
      } else {
         server->send(200, APPLICATION_JSON_TYPE, "No");
      }
    } else {
      if (_isSerial) {
        Serial.println("onLoginHandler: pass not found");
      }
      server->send(200, APPLICATION_JSON_TYPE, "passwod empty");
    }
  } else {
    if (_isSerial) {
      Serial.println("onLoginHandler: ssid not found");
    }
    server->send(200, APPLICATION_JSON_TYPE, "ssid empty");
  }

}

//void WebModule::onLoginHandler() {
//  String response;
//  if (server->hasArg("ssid") && server->arg("ssid") != "") {
//    if (server->hasArg("pass") && server->arg("pass") != "") {
//      sendFile(LOADING_PAGE_PATH, HTML_CONTENT_TYPE);
//      createWorkStation(server->arg("ssid"), server->arg("pass"));
//    } else {
//      if (_isSerial) {
//        Serial.println("onLoginHandler: pass not found");
//      }
//      response = getFileAsString(ERROR_PAGE_PATH);
//      response.replace("{{error}}", "Password is empty");
//      server->send(200, HTML_CONTENT_TYPE, response);
//    }
//  } else {
//    if (_isSerial) {
//      Serial.println("onLoginHandler: ssid not found");
//    }
//    response = getFileAsString(ERROR_PAGE_PATH);
//    response.replace("{{error}}", "SSID is empty");
//    server->send(200, HTML_CONTENT_TYPE, response);
//  }
//
//}

void WebModule::onNotFoundHandler() {
  if (!onFileHandler(server->uri())) {
    redirectToMain();
  }
}

void WebModule::onMainHandler() {
  if (_isSerial) {
    Serial.println("onMainHandler");
  }
  if (_isWS == true) {
    if(_isSerial) {
      Serial.println("isWS = true");
    }
    String response = getFileAsString(WS_PAGE_PATH);
    response.replace("{{ssid}}", _networkSsid);
    server->send(200, HTML_CONTENT_TYPE, response);
  } else {
    if (_isAP == true) {
      if(_isSerial) {
        Serial.println("isAP = true");
        Serial.println("errorMessage " + _errorMessage);
      }
      String response = getFileAsString(AP_PAGE_PATH);
      if(_errorMessage != "") {
        response.replace("{{error}}", _errorMessage);
        _errorMessage = "";
      } else {
        response.replace("{{error}}", "");
      }
      server->send(200, HTML_CONTENT_TYPE, response);
    } else {
      server->send(404, "text/plain");
      if (_isSerial) {
        Serial.println("sever sent 404");
      }
    }
  }
}

bool WebModule::onFileHandler(String url) {
  String contentType = getContentType(url);
  if (contentType != "") {
    sendFile(url, contentType);
  } else {
    return false;
  }
}

void WebModule::onDisconnect() {
  if (_isSerial) {
    Serial.println("disconnect from wifi");
  }
  WiFi.disconnect ();
  _isWS = false;
  _networkSsid="";
  redirectToMain();
}

void WebModule::handleServer(String type, String vers) {
  server->handleClient();
  if(_isWS == true && millis() - lastGreetingTime > _pingTime) {
    lastGreetingTime = millis();
    sendGreeting(WiFi.macAddress(), type, vers);
  }
}

void WebModule::sendFile(String path, String contentType) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server->streamFile(file, contentType); // And send it to the client
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

void WebModule::redirectToMain() {
  if (_isSerial) {
    Serial.println("redirect from " + server->uri() + " to /main");
  }
  server->sendHeader("Location", "/main");
  server->send(303);
}

String WebModule::getContentType(String filename) {
  if (filename.endsWith(".html")) return HTML_CONTENT_TYPE;
  else if (filename.endsWith(".css")) return CSS_CONTENT_TYPE;
  else if (filename.endsWith(".js")) return JS_CONTENT_TYPE;
  else if (filename.endsWith(".ico")) return ICON_CONTENT_TYPE;
  return "";
}

void WebModule::sendGreeting(String mac, String type, String vers){
  if (WiFi.status() == WL_CONNECTED) {
    String message = mac + "|" + type + "|" + vers;
    if (_isSerial) {
      Serial.println("send greeting: " + message);
    }
    char msg[255];
    message.toCharArray(msg,255);
    if (_isSerial) {
      Serial.println("local ip: " + WiFi.localIP().toString());
      Serial.println(WiFi.status());
    }

    udp->beginPacketMulticast(*multicastAddress, MULTICAST_PORT, WiFi.localIP());
    udp->write(msg);
    udp->endPacket();
  } else if (_isSerial){
    Serial.println("WiFi.localIP() is null");
  } 
}

void WebModule::onGetNetworkInfo() {
  int result;
  if (_isWS) {
    if(_isAP) {
      result = 2; 
    } else {
      result = 1;
    }
  } else if (_isAP){
    result = 0;
  }
  server->send(200, APPLICATION_JSON_TYPE, String(result));      
}

void WebModule::onGetPingTime(){
  server->send(200, APPLICATION_JSON_TYPE, String(_pingTime));
}

void WebModule::onSetPingTime(){
  if(server->hasArg("time")) {
    _pingTime = server->arg("time").toInt();
    server->send(200, APPLICATION_JSON_TYPE, String(true));
  } else {
    server->send(200, APPLICATION_JSON_TYPE, String(false));
  }
      
}
    
void WebModule::onGetServerIp() {
      server->send(200, APPLICATION_JSON_TYPE, _networkSsid);
}
