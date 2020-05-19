## Dictionary
| Term | Description |
|--|--|
|AP|Access point (like wifi)|
|WS|Workstation (like device connected to wifi)|
### How to setup environment
- open arduinoIDE -> File -> Preferences
- enter "http://arduino.esp8266.com/stable/package_esp8266com_index.json" to "Additional Boards Manager url"
- go to Tools -> Board -> Boards Manager
- install esp8266 be ESP8266 Community 2.6.3

### How connect esp8266 to TTL
| TTL | ESP8266 |
| - | - |
| 3V3 | 3V3 |
|     | EN  |
| TXD | RXD |
| RXD | TXD |
| GND | GND |
|     | IO0 (if need to write sketch)|
|||

### How to connect to esp8266 in AP
got to 192.168.4.1 - default gateway