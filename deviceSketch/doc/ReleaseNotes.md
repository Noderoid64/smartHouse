## Device Rest
### 0.1.5
#### Common
| Url| Description |
|--| -- |
| /main | returns main page |
|/disconnect| disconnect from wifi|
|/login?ssid=&pass=| connect to network with ssid and pass|
|/network-info|return 0 - if AP, 1 - if WS, 2 if WS and AP|
|/ping/get|return _ping|
|/ping/set| set _ping|
|/server/get| return _networkSsid|

#### Socket
|Url|Description|
|--|--|
|/on|turn on the socket|
|/off| turn off|
|/status|get LOW or HIGHT|
|/info| <device_version> \| <device_type>|