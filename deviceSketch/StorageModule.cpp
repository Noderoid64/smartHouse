#include "storageModule.h"
#include <FS.h>

#define NET_CONFIG_FILENAME "NET_CONF.txt"
#define SSID_POSITION 0
#define PASS_POSITION 1
#define ISWS_POSITION 2
#define ISAP_POSITION 3
#define TYPE_POSITION 4
#define VERS_POSITION 5
#define OFFSET_BYTES 32

#define TRUE "TRUE"
#define FALSE "FALSE"

StorageModule::StorageModule(String version, String type) {
  SPIFFS.begin();
  setVersion(version);
  setType(type);
}

void StorageModule::ClearAll() {
  setSsid("");
  setPass("");
  setIsWS(false);
  setIsAP(false);
}

void StorageModule::setSsid(String value) {
  proxyInput(SSID_POSITION, value);
}

String StorageModule::getSsid() {
  return proxyOutput(SSID_POSITION);
}

void StorageModule::setPass(String value) {
  proxyInput(PASS_POSITION, value);
}

String StorageModule::getPass() {
  return proxyOutput(PASS_POSITION);  
}

bool StorageModule::getIsWS() {
  return proxyOutput(ISWS_POSITION) == TRUE;  
}

void StorageModule::setIsWS(bool value) {
  if(value == true){
    proxyInput(ISWS_POSITION, TRUE);
  } else {
    proxyInput(ISWS_POSITION, FALSE);
  }
}

bool StorageModule::getIsAP() {
  return proxyOutput(ISAP_POSITION) == TRUE;  
}

void StorageModule::setIsAP(bool value) {
  if(value == true){
    proxyInput(ISAP_POSITION, TRUE);
  } else {
    proxyInput(ISAP_POSITION, FALSE);
  }
}

String StorageModule::getType() {
   return proxyOutput(TYPE_POSITION);
}

void StorageModule::setType(String value) {
   proxyInput(TYPE_POSITION, value);
}

String StorageModule::getVersion() {
  return proxyOutput(VERS_POSITION);
}

void StorageModule::setVersion(String value) {
  proxyInput(VERS_POSITION, value);
}

void StorageModule::proxyInput(int param, String value) {
  File file;
  if (SPIFFS.exists(NET_CONFIG_FILENAME)) {
    file = SPIFFS.open(NET_CONFIG_FILENAME, "r+");
  } else {
    file = SPIFFS.open(NET_CONFIG_FILENAME, "w+");
  }
  if (!file) {
    Serial.println("UPs");
  } else {
    file.seek(param * OFFSET_BYTES, SeekSet);
    if (value.length() <= OFFSET_BYTES) {
      for(int i =0; i< OFFSET_BYTES; i++) {
        file.write(255);
      }
      file.seek(param * OFFSET_BYTES, SeekSet);
      file.print(value);  
    } else {
      // log error
    }
  }
  file.close();
}

String StorageModule::proxyOutput(int param) {
  if (SPIFFS.exists(NET_CONFIG_FILENAME)) {
    File file = SPIFFS.open(NET_CONFIG_FILENAME, "r");
    if (!file) {
      Serial.println("UPs");
    } else {
      file.seek(param * OFFSET_BYTES,SeekSet);
      String result;
      int count = 0;
      int b = file.read();
      while (b != -1 && b != 255 && count < OFFSET_BYTES) {
        result += char(b);
        b = file.read();
        count++;
      }
      file.close();
      return result;
    }
    file.close();
  }
}
