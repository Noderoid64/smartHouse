#include "commonModule.h"
#include <FS.h>

#define NET_CONFIG_FILENAME "NET_CONF.txt"
#define SSID_POSITION 0
#define PASS_POSITION 1
#define OFFSET_BYTES 32

CommonModule::CommonModule() {
  SPIFFS.begin();
}

void CommonModule::setSsid(String value) {
  proxyInput(SSID_POSITION, value);
}

String CommonModule::getSsid() {
  return proxyOutput(SSID_POSITION);
}

void CommonModule::setPass(String value) {
  proxyInput(PASS_POSITION, value);
}

String CommonModule::getPass() {
  return proxyOutput(PASS_POSITION);  
}




void CommonModule::proxyInput(int param, String value) {
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

String CommonModule::proxyOutput(int param) {
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
        Serial.println(b);
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
