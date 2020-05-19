using System;
using Server.Model.Value;

namespace Server.Model.Entity {
    public class DeviceEntity {
        public int id {get; set;}
        public DeviceType type {get; set;}
        public DeviceVersion version {get; set;}
        public String ipAddress {get; set;}
        public String macAddress {get; set;}
        public bool? isNew {get;set;}
        public DateTime lastPing {get;set;}
    }

}