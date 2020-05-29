import 'dart:developer';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';

import 'new-device-dialog/new-device-dialog.widget.dart';

class NewDeviceIconViewModel extends ChangeNotifier {
   void showSsidDialog(BuildContext context) {
     showDialog(
         context: context,
         child: new NewDeviceDialogWidget()
     );
    log("ups");
  }
}
