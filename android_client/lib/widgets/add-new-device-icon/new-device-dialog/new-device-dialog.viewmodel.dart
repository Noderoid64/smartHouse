import 'dart:developer';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';

import '../../../services/web/device-rest.service.dart';

class NewDeviceDialogViewModel extends ChangeNotifier {
  GlobalKey formKey = GlobalKey<FormState>();
  final ssidController = TextEditingController();
  final deviceRestService = new DeviceRestService();
  String ssid;

  String ssidValidatorFunction(String value) {
    if (value.isEmpty) {
      return 'Please enter some text';
    } else if (value.length < 8) {
      return 'Please enter more than 8 chars';
    }
    return null;
  }

  void getSsid (String ssid) {
    this.ssid = ssid;
  }

  void submitButtonPressed() async {

    String pass = ssidController.value.text;
    log(ssid + " " + pass);
    bool good = await deviceRestService.login(ssid, pass);
    log(good.toString());
  }

  @override
  void dispose() {
    ssidController.dispose();
    super.dispose();
  }


}
