using System.Threading.Tasks;
using System.Collections.Generic;
using Server.Domain.Model.Entity;

namespace Server.Domain.Repositories {
    public interface IDeviceRepository : IBaseRepository<DeviceEntity> {
        Task<IEnumerable<DeviceEntity>> listAsync(); 

        Task<DeviceEntity> GetByMac(string mac);
    }
}