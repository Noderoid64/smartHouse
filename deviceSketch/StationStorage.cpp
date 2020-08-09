#include "StationStorage.h"


void DataCell::setTemperature(float value) {
    round(value);
}

 void setHumidity(float value);
 void setAir(int value);

 float getTemperature();
 int getHumidity();
 int getAir();

  private:
  unsigned char temperature;
  unsigned char humidity;
  unsigned char air;
