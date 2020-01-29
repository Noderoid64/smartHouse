using System.Threading.Tasks;
using System.Collections.Generic;
using Server.Domain.Model.Entity;

namespace Server.Domain.Services {
    public interface IDeviceService {
        Task<IEnumerable<DeviceEntity>> asyncList();
        void persistAsync(DeviceEntity entity);
    }
}