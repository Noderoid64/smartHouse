import 'dart:developer';

import 'package:android_client/screens/devices/socket-device.screen.dart';
import 'package:android_client/screens/loading.screen.dart';
import 'package:flutter/material.dart';
import 'screens/devices.screen.dart';

void main() {
  return runApp(MaterialApp(
    title: "material app title",
    theme: ThemeData(
// Define the default brightness and colors.
      brightness: Brightness.dark,
      primaryColor: Colors.grey[700],
      accentColor: Colors.lightGreen[700],
    ),
    initialRoute: "/",
    routes: {
      "/": (context) => LoadingScreen(),
      "devices": (context) => DeviceScreen(),
      "socket": (context) => SocketDeviceScreen()
    },
  ));
}

