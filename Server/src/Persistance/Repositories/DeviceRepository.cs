using System.Collections.Generic;
using System.Threading.Tasks;
using System.Linq;
using Microsoft.EntityFrameworkCore;

using Server.Persistance.Contexts;
using Server.Model.Entity;

namespace Server.Persistance.Repositories
{
    public class DeviceRepository : BaseRepository<DeviceEntity>
    {
        public DeviceRepository(AppDbContext context) : base(context, context.deviceEntities) { }

        public async Task<IEnumerable<DeviceEntity>> listAsync()
        {
            return await context.deviceEntities.ToArrayAsync();
        }

        public Task<DeviceEntity> GetByMac(string mac)
        {
            if (!string.IsNullOrEmpty(mac))
            {
                return context.deviceEntities.FirstOrDefaultAsync(el => el.macAddress.Equals(mac));
            }
            return Task.FromResult<DeviceEntity>(null);
        }

        public Task<IEnumerable<DeviceEntity>> getNewDevices()
        {
            return Task<IEnumerable<DeviceEntity>>.Run(() => {
                IEnumerable<DeviceEntity> query = from device in context.deviceEntities
                where device.isNew == true
                orderby device.id ascending
                select device;
                return query;
            });
        }
    }
}