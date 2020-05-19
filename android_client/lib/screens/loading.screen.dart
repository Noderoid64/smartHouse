import 'package:android_client/models/device-info-response.model.dart';
import 'package:android_client/models/screen-models/socket-device-screen.model.dart';
import 'package:android_client/services/udp-client.service.dart';
import 'package:android_client/services/web/device-rest.service.dart';
import 'package:flutter/material.dart';

import 'package:flutter_spinkit/flutter_spinkit.dart';

class LoadingScreen extends StatefulWidget {
  @override
  State createState() {
    return _LoadingScreenState();
  }
}

class _LoadingScreenState extends State<LoadingScreen> {
  String labelMessage = "Searching for device...";
  DeviceRestService deviceRestService = DeviceRestService();
  UdpClientService udpClientService = UdpClientService();
  bool isLoadingEnds = false;

  _LoadingScreenState() {
    searchDevices();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Colors.grey[700],
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              isLoadingEnds
                  ? IconButton(
                      icon: Icon(Icons.autorenew),
                      iconSize: 150,
                      tooltip: 'Increase volume by 10',
                      onPressed: () {
                        Navigator.pushReplacementNamed(context, "/");
                      },
                    )
                  : SpinKitCircle(
                      color: Colors.lightGreen[500],
                      size: 150.0,
                    ),
              Text(labelMessage, style: TextStyle(fontSize: 20.0))
            ],
          ),
        ));
  }

  void searchDevices() async {
    DeviceInfoResponse response = await deviceRestService.getInfo();
    if (response != null) {
      // Device was found
      Navigator.pushReplacementNamed(context, "socket", arguments: SocketDeviceScreenModel(response.ipAddress, true));
      setState(() => labelMessage = response.type);
    } else {
      setState(() => labelMessage = "Searching for the server...");
      udpClientService.sendServerBroadCastAsync((response) {
        if (response != null) {
          // Server found
          Navigator.pushReplacementNamed(context, "devices");
        } else {
          // Nothing was found
          setState(
              () => {labelMessage = "No server or device was found. \n Please connect and try again", isLoadingEnds = true});
        }
      });
    }
  }
}
