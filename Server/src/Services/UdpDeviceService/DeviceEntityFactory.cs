using System;
using System.Net;
using Server.Model.Entity;
using Server.Model.Value;

using Serilog;
using Serilog.Events;

namespace Server.Services.UdpDeviceServices {
    public class DeviceEntityFactory {
        private readonly bool _isDebug = Log.IsEnabled(LogEventLevel.Debug);
        public DeviceEntity build(string message, IPEndPoint source) {
            DeviceEntity result = new DeviceEntity();
            string [] parts = message.Split('|');
            if (parts.Length == 3) {
                result.ipAddress = source.Address.ToString();
                result.macAddress = parts[0];
                result.version = new DeviceVersion(parts[2]);
                result.type = getDeviceType(parts[1]);
                result.isNew = true;
                result.lastPing = DateTime.Now;
            } else {
                Log.Warning("Message split not to 3 parts");
                Log.Warning("The message is {0}", message);
                result = null;
            }
            return result;
        }

        private DeviceType getDeviceType(string message) {
            switch(message) {
                case "S": return DeviceType.SOCKET;
                case "L": return DeviceType.LED;
                case "D": return DeviceType.DIODE;
                case "CLIENT": return DeviceType.CLIENT;
                case "M": return DeviceType.MANAGED_SERVER;
                default: return DeviceType.OTHER;
            }
        }
    }
}