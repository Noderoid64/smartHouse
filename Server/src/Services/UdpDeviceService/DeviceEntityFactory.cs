using System;
using System.Net;
using Server.Domain.Model.Entity;
using Server.Domain.Model.Value;

namespace Server.Services.UdpDeviceServices {
    public class DeviceEntityFactory {
        public DeviceEntity build(string message, IPEndPoint source) {
            DeviceEntity result = new DeviceEntity();
            string [] parts = message.Split('|');
            if (parts.Length == 3) {
                result.ipAddress = source.Address.ToString();
                result.macAddress = parts[0];
                result.version = new DeviceVersion(parts[2]);
                result.type = getDeviceType(parts[1]);
            } else {
                throw new Exception ("DeviceEntityFactory: message has been splitted not to 3 parts");
            }
            return result;
        }

        private DeviceType getDeviceType(string message) {
            switch(message) {
                case "S": return DeviceType.SOCKET;
                case "L": return DeviceType.LED;
                case "D": return DeviceType.DIODE;
                default: return DeviceType.OTHER;
            }
        }
    }
}