class DeviceInfoResponse {
  String version;
  String type;
  String ipAddress;

  DeviceInfoResponse(String _version, String _type, String _ipAddress) {
    version = _version;
    type = _type;
    ipAddress = _ipAddress;
  }
}
