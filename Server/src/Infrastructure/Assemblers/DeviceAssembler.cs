using System;
using System.Net;

using Serilog;
using Serilog.Events;

using Server.Domain;
using Server.Domain.Entity;
using Server.Domain.Value;
using Server.Infrastructure.Model;

namespace Server.Infrastructure.Assemblers {
    public class DeviceAssembler {

        private readonly bool _isDebug = Log.IsEnabled(LogEventLevel.Debug);

        public Device assemble(UdpMessage deviceInfo) {
            AssertTool.notNull(deviceInfo, "deviceInfo");
            DeviceEntity entity = new DeviceEntity();
            entity.ipAddress = deviceInfo.ip;
            entity.lastPing = deviceInfo.lastPing;
            entity.type = getType(deviceInfo.type);
            entity.macAddress = deviceInfo.macAddress;
            entity.version = new DeviceVersion(deviceInfo.version);
            return new Device(entity);
        }

        private DeviceType getType(string type) {
            switch (type) {
                case "S": return DeviceType.SOCKET;
                case "C": return DeviceType.CLIENT;
                default: return DeviceType.OTHER;
            }
        }
    }
}
