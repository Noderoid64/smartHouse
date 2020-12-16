#include "Store.h"
#include <FS.h>
#include <Arduino.h>

#define EN_SER
#define TRUE "true"
#define FALSE "false"

#define FILE_NAME "Storage.txt"
#define CELL_SIZE 32

Store::Store() {
  if(SPIFFS.begin())
  {
    #ifdef EN_SER
    Serial.println("SPIFFS Initialization ok");
    #endif
  } else {
    #ifdef EN_SER
    Serial.println("SPIFFS Initialization failed");
    #endif
  }
}

bool Store::getBool(store_param param) {
  String res = this->get(param);
  if (res == TRUE) {
    return true;
  } else {
    return false;
  }
}

void Store::setBool(bool value, store_param param) {
  String res = value ? TRUE : FALSE;
  this->set(res, param);
}

String Store::get(store_param param) {
  String result = "";
  File f = SPIFFS.open(FILE_NAME, "r");
  if (f) {
    #ifdef EN_SER
    Serial.print("File opened to get ");
    Serial.println(param);
    #endif
    f.seek(CELL_SIZE * param, SeekSet);
    result = f.readStringUntil('\n');
    f.close();
  } else {
    #ifdef EN_SER
    Serial.println("Can not open file");
    #endif
  }
  Serial.println("value: " + result);
  return result.substring(0,result.length() - 1);
}

void Store::set(String value, store_param param) {
  if (value.length() >= CELL_SIZE) {
    #ifdef EN_SER
    Serial.println("value is longer than cell size");
    #endif
    return;
  }
  File f = SPIFFS.open(FILE_NAME, "r+");
  if (f) {
    #ifdef EN_SER
    Serial.print("File opened to set ");
    Serial.print(param + "\t");
    Serial.println(value);
    #endif
    f.seek(CELL_SIZE * param, SeekSet);
    f.println(value);
    f.close();
  } else {
    #ifdef EN_SER
    Serial.println("Can not open file");
    #endif
  }
}

void Store::format() {
  SPIFFS.format();
}
