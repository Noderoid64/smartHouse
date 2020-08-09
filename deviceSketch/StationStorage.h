#ifndef STATION_STORAGE_H
#define STATION_STORAGE_H

class DataCell {

  public:
  void setTemperature(float value);
  void setHumidity(float value);
  void setAir(int value);

  float getTemperature();
  int getHumidity();
  int getAir();

  private:
  unsigned char temperature;
  unsigned char humidity;
  unsigned char air;
}

class StationStorage {
  public:
    StationStorage(bool isSerial);
    void setInterval(unsigned short int interval);
    unsigned short int getInterval();
    void setValue(Cell value);
    Cell getValue(int from, int to);
  private:
    unsigned short char pointer;
    void getHumidity(ESP8266WebServer*);
    void getTemperature(ESP8266WebServer*);
    void getAirQuality(ESP8266WebServer*);
};

#endif
