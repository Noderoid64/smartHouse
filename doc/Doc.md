## DeviceSketch
### Acrhitecture
 - NetModule - responsible for connection/disconnection and udp messaging
 - WebModule - register common and optional handlers

### Udp messages
| mac | type | version | command | data |
#### Common commands
|command|description|
| -- | -- |
|0|ask to connect to the server|
|1|update system status|
|...|...|
|41| send temperature 4 bytes |
|42| send humidity 4 bytes |
|43| send CO2 4 bytes |