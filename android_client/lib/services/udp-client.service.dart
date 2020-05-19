import 'package:udp/udp.dart';
import 'dart:developer';
import 'dart:io';

class UdpClientService {

  static final UdpClientService _singleton = UdpClientService._internal();
  factory UdpClientService() {
    return _singleton;
  }

  UdpClientService._internal();

  int port = 4446;
  String broadcastIp = "230.0.0.0";

  sendServerBroadCastAsync(Function function) async {
    var DESTINATION_ADDRESS = InternetAddress(broadcastIp);
    log("send broadcast");
    var receiver = await UDP.bind(Endpoint.multicast(InternetAddress(broadcastIp), port: Port(port)));
    await receiver.send('00:00:00:00:00:00|CLIENT|0.1.0'.codeUnits, Endpoint.broadcast(port: Port(port)));
    await receiver.listen((datagram) {
      String str = String.fromCharCodes(datagram.data);
      log("govno");
      log(str);
      List<String> parts = str.split("|");
      log(parts.length.toString());
      log(parts.elementAt(1));
      if (parts.length == 3 && parts.elementAt(1) == "MANAGED_SERVER") {
        function(datagram.address.address.toString());
      }
    }, timeout: Duration(seconds: 4));
    function(null);
    receiver.close();
  }
}