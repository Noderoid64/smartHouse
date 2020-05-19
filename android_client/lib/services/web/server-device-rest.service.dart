class ServerDeviceRestService {
  static final ServerDeviceRestService _singleton = ServerDeviceRestService._internal();
  factory ServerDeviceRestService() {
    return _singleton;
  }
  ServerDeviceRestService._internal();
}