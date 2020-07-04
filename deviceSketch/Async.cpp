#include <list>
#include <functional>
#include <arduino.h>
#include "Async.h"

struct TimedCallback {
  std::function<void()> callback;
  long time;
};

std::list<TimedCallback> callbacks;

void setTimeout(long time, std::function<void()> func) {
  TimedCallback item;
  item.callback = func;
  item.time = millis() + time;
  callbacks.push_back(item);
}

void asyncTick() {
  std::list<TimedCallback>::iterator i = callbacks.begin();
  while (i != callbacks.end()) {
    if (millis() >= i->time) {
      i->callback();
      callbacks.erase(i++);
    }
    else {
      i++;
    }
  }
}
