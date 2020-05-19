import 'package:android_client/services/web/device-rest.service.dart';
import 'package:http/http.dart' as http;

class DeviceSocketRestService extends DeviceRestService {

  Future<String> getStatus([String ip = "192.168.4.1"]) async {
    final response = await http.get(url + ip + '/status');
    return handleRequest(response);
  }

  Future<String> turnOn([String ip = "192.168.4.1"]) async {
    return handleRequest(await http.get(url + ip + '/on'));
  }

  Future<String> turnOff([String ip = "192.168.4.1"]) async {
    return handleRequest(await http.get(url + ip + '/off'));
  }
}