import 'dart:developer';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';

class NewDeviceDialogViewModel extends ChangeNotifier {
  GlobalKey formKey = GlobalKey<FormState>();
  final ssidController = TextEditingController();

  String ssidValidatorFunction(String value) {
    if (value.isEmpty) {
      return 'Please enter some text';
    } else if (value.length < 8) {
      return 'Please enter more than 8 chars';
    }
    return null;
  }

  void submitButtonPressed() {
    log(ssidController.value.text);
  }

  @override
  void dispose() {
    ssidController.dispose();
    super.dispose();
  }


}
