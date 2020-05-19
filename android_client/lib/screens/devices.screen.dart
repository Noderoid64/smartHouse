
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class DeviceScreen extends StatelessWidget {

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Devices'),
      ),
      body: Center(
        child: RaisedButton(
          child: Text('press me'),
          onPressed: () {

          },
        ),
      ),
    );
  }
}