import 'package:android_client/models/screen-models/socket-device-screen.model.dart';
import 'package:android_client/services/web/device-socket-rest.service.dart';
import 'package:android_client/widgets/add-new-device-icon/new-device-icon.widget.dart';
import 'package:flutter/material.dart';

class SocketDeviceScreen extends StatefulWidget {
  @override
  State createState() {
    return _SocketDeviceState();
  }
}

class _SocketDeviceState extends State<SocketDeviceScreen> {
  DeviceSocketRestService socketRestService = DeviceSocketRestService();
  bool status = false;

  _SocketDeviceState() {
    socketRestService.getStatus().then((String result) {
      status = result == 'LOW' ? false : true;
    });
  }

  @override
  Widget build(BuildContext context) {
    SocketDeviceScreenModel routeModel =
        ModalRoute.of(context).settings.arguments;
    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false,
        title: Text("Socket"),
        actions: <Widget>[
//          routeModel.isNewDevice
              NewDeviceIconWidget()
        ],
      ),
      body: Center(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Ink(
              decoration: ShapeDecoration(
                color: status ? Colors.lightGreen : Colors.grey,
                shape: CircleBorder(),
              ),
              child: IconButton(
                icon: Icon(Icons.lightbulb_outline),
                color: Colors.white,
                iconSize: 120.0,
                onPressed: () {
                  if (this.status) {
                    this
                        .socketRestService
                        .turnOff(routeModel.ip)
                        .then((String result) {
                      setState(() {
                        this.status = false;
                      });
                    });
                  } else {
                    this
                        .socketRestService
                        .turnOn(routeModel.ip)
                        .then((String result) {
                      setState(() {
                        this.status = true;
                      });
                    });
                  }
                },
              ),
            ),
          ],
        ),
      ),
    );
  }
}
