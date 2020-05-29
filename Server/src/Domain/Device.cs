using System;
using System.Threading.Tasks;

using Server.Domain.Entity;
using Server.Infrastructure;
using Server.Infrastructure.Persistance;


namespace Server.Domain {
    public class Device : BaseDomainModel<DeviceEntity> {
        public Device (DeviceEntity entity): base(entity) {}

        public static async Task<Device> findByMac(DeviceRepository repository, string mac) {
            AssertTool.notNull(mac, "mac");
            AssertTool.notNull(repository, "deviceRepository");
            DeviceEntity entity = await repository.GetByMac(mac);
            return new Device(entity);
        }

        public void updateIp(string ip) {
            AssertTool.notNull(ip, "ip");
            this.entity.ipAddress = ip;
        }

        public void updatePing() {
            this.entity.lastPing = DateTime.Now;
        }
    }
}