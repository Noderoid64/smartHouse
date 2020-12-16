#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <vector>
#include "Store.h";
#include "UdpModule.h";
#include "LogicSocket.h"

#define EN_SER
#define TYPE "socket"
#define VERSION "0.0.1"

#define SSID "Esp9266Nod"
#define SSID_PARAM "ssid"
#define PASS_PARAM "pass"

ESP8266WebServer server(80);
Store store;
UdpModule udpModule = UdpModule();
Logic logic = Logic(&store);

void startSoftAP() {
  bool result =  WiFi.softAP(SSID);
  #ifdef EN_SER
  if (result) {
    Serial.println("SoftAp start");
  } else {
    Serial.println("SoftAp failed");
  }
  #endif
}

void stopSoftAP() {
  boolean result = WiFi.softAPdisconnect(false);
  #ifdef EN_SER
  if (result) {
    Serial.println("Disconnected from softAP");
  } else {
    Serial.println("Failed disconnected from SoftAP");
  }
  #endif
}

void connectToWiFi(String ssid, String pass, std::function<void()> onConnect, std::function<void()> onError) {
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() == WL_DISCONNECTED || WiFi.status() == WL_CONNECT_FAILED)
  {
    delay(250);
  }
  if (WiFi.status() == WL_CONNECTED) {
    #ifdef EN_SER
    Serial.println("Connected to WiFi");
    #endif
    onConnect();
  } else {
    #ifdef EN_SER
    Serial.println("Connection failed, status");
    Serial.println(WiFi.status());
    onError();
    #endif
  }
}

void connectTo() {
  Serial.println("Connected");
  if (server.hasArg(SSID_PARAM) && server.hasArg(PASS_PARAM) && server.arg(SSID_PARAM) != NULL && server.arg(PASS_PARAM)) {
    connectToWiFi(server.arg(SSID_PARAM), server.arg(PASS_PARAM), [&] () {
      Serial.println("ssid");
      Serial.println(server.arg(SSID_PARAM));
      store.set(server.arg(PASS_PARAM), S_PASS);
      store.set(server.arg(SSID_PARAM), S_SSID);
      server.send(200, "text/plain", "{message: 'Ok'}");
      delay(100);
      stopSoftAP();  
    }, [](){});
  } else {
    server.send(200, "text/plain", "{message: 'Error'}");
    #ifdef EN_SER
    Serial.println("Something with params");
    #endif
  }
}

void disconnectFrom() {
  #ifdef EN_SER
  Serial.println("DisconnectFrom");
  #endif
  boolean result = WiFi.disconnect();
  if (result) {
    startSoftAP();
    store.set("", S_SSID);
    store.set("", S_PASS);
    server.send(200, "text/plain", "disconnected");
  } else {
    #ifdef EN_SER
    Serial.println("Can not disconnect");
    #endif
    server.send(200, "text/plain", "error");
  }
}

void setup() {
  Serial.begin(115200);
  delay(6000);
//   Try to connect to wifi
  String ssid = store.get(S_SSID);
  String pass = store.get(S_PASS);
  if (ssid != "" && pass != "") {
    connectToWiFi(ssid, pass, [](){}, [](){
      startSoftAP();
    });
  } else {
    startSoftAP();
  }
  server.on("/connect", connectTo);
  server.on("/disconnect", disconnectFrom);
  logic.registerHandlers(&server);
  server.begin();
  
}

void loop() {
  server.handleClient();
  udpModule.handleUDP(TYPE, VERSION);
  delay(1000);
  Serial.println("Tick");
  
}
