using System;
using Server.Domain.Model.Value;

namespace Server.Domain.Model.Entity {
    public class DeviceEntity {
        public int id {get; set;}
        public DeviceType type {get; set;}
        public DeviceVersion version {get; set;}
        public String ipAddress {get; set;}
        public String macAddress {get; set;}
    }

}