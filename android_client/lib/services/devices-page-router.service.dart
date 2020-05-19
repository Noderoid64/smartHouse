import 'package:flutter/material.dart';

class DevicePageRouter {
  static final DevicePageRouter _singleton = DevicePageRouter._internal();
  factory DevicePageRouter() {
    return _singleton;
  }
  DevicePageRouter._internal();

  void route(String deviceType, String ip, BuildContext context) {
    switch(deviceType) {
      case "SOCKET": {
        Navigator.pushNamed(
          context,
          "socket",
          arguments: ip,
        );
      } break;
    }

  }

}
