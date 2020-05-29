import 'dart:developer';

import 'package:flutter/material.dart';
import 'package:wifi_iot/wifi_iot.dart';

class SsidDropdownWidget extends StatefulWidget {
  Key key;
  Function onSubmit;

  SsidDropdownWidget(Key _key, Function onSubmit) {
    key = _key;
    this.onSubmit = onSubmit;
  }
  @override
  State createState() {
    return _SsidDropdownWidgetState(key, onSubmit);
  }
}

class _SsidDropdownWidgetState extends State<SsidDropdownWidget> {
  GlobalKey<FormFieldState> key = GlobalKey<FormFieldState>();
  List<String> list = [];
  String _value;
  Function onSubmit;

  _SsidDropdownWidgetState(Key _key, Function onSubmit) {
    key = _key;
    this.onSubmit = onSubmit;
    loadWifis();
  }

  loadWifis () async {
    WiFiForIoTPlugin.isEnabled().then((value) async {
      List<WifiNetwork> _list = await WiFiForIoTPlugin.loadWifiList();
      log("hello wifi");

      if (_list != null && _list.length > 0) {
        log(_list.elementAt(0).ssid);
        List<String> res = _list.map((WifiNetwork element) { return element.ssid; }).toSet().toList();
        setState(() {
          list = res;
        });
      } else {
        log("list is null or empty");
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return DropdownButton<String>(
      key: key,
      items: list.map((String result) {
        return DropdownMenuItem(
          value: result,
          child: Text(
            result
          ),
        );
      }).toList(),
      onChanged: (value) {
        setState(() {
          _value = value;
          onSubmit(_value);
        });
      },
      value: _value,
      isExpanded: true,
    );
  }
}
