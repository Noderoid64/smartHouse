import 'dart:developer';

import 'package:android_client/models/device-info-response.model.dart';
import 'package:http/http.dart' as http;

class DeviceRestService {
  String url = "http://";

  Future<DeviceInfoResponse> getInfo([String ip = "192.168.4.1"]) async {
    DeviceInfoResponse response;
    try {
      var rawResponse = await http.get(url + ip + '/info', ).timeout(Duration(seconds: 6));
      String stringResponse = handleRequest(rawResponse);
      log(stringResponse);
      if (stringResponse != null) {
        List<String> parts = stringResponse.split('|');
        response = DeviceInfoResponse(parts.elementAt(0), parts.elementAt(1), ip);
        log(response.ipAddress);
        return response;
      }
      response = null;
    } catch (e) {
      log(e.toString());
      response = null;
    }
  }

  Future<bool> login(String ssid, String password, [String ip = "192.168.4.1"]) async {
    if (ssid != null && ssid.length >= 6 && password != null && password.length >=8) {
      final response = await http.get(url + ip + '/login?ssid=' + ssid + "&pass=" + password, );
      log(response.body);
      return response.statusCode == 200 ? true : false;
    }
    return null;
  }

  handleRequest(http.Response response) {
    if (response != null) {
      if (response.statusCode == 200) {
        return response.body;
      } else {
        log("response code: {response.statusCode}");
      }
    } else {
      log("response is null");
      return null;
    }
  }

}
