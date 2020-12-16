#include "UdpModule.h"
#include <Udp.h>
#include <ESP8266WiFi.h>

#define BUFFER_SIZE 256
#define PORT 4096
#define DEVIDER '/'
char incomingPacket[BUFFER_SIZE];

UdpModule::UdpModule() {
  multicastAddress = new IPAddress(226,1,1,1);
  udpClient->beginMulticast(WiFi.localIP(), *multicastAddress, PORT);
}

void UdpModule::handleUDP(String type, String version) {
  int packetLength = udpClient->parsePacket(); 
    if(packetLength){
        int len = udpClient->read(incomingPacket, BUFFER_SIZE);
        if (len > 0){
            incomingPacket[len] = 0;
            String result = String(incomingPacket);
            int index = result.indexOf(DEVIDER);
            String senderIp = result.substring(0,index);
            char command = result.charAt(index + 1);
            String data = result.substring(index + 3); // Should skip "/0/" (slash + command (1 sybmol) + slash)

            #ifdef EN_SER
            Serial.print("sender: ");
            Serial.println(senderIp);
            Serial.print("command: ");
            Serial.println(command);
            Serial.print("data: ");
            Serial.println(data);
            #endif

            String ip = WiFi.localIP().toString();

            if (command == '0') {
              sendUdp(senderIp, ip + "/1");
            } else if (command == '2') {
              String mac = WiFi.macAddress();
              sendUdp(senderIp, ip + "/3/" + mac + "/" + type + "/" + version);
            } else {
              Serial.println("command: " + command);
            }
            
        }
    }
}

void UdpModule::sendUdp(String ip, String message) {
  char msg[BUFFER_SIZE];
  message.toCharArray(msg,BUFFER_SIZE);
  ip.trim();
  IPAddress pi;
  pi.fromString(ip);
  udpClient->beginPacket(pi, PORT);
  udpClient->write(msg);
  udpClient->endPacket();
}
