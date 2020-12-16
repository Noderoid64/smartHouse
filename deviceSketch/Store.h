#ifndef STORE
#define STORE

#include <Arduino.h>

typedef enum {
  S_SSID = 0,
  S_PASS = 1,
  S_FREE = 3
} store_param;

class Store {
  public: 
  Store();
  String get(store_param);
  bool getBool(store_param);
  void set(String value, store_param);
  void setBool(bool value, store_param);
  void format();
};


#endif
