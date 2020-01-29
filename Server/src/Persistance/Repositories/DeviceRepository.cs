using System.Collections.Generic;
using System.Threading.Tasks;
using Server.Persistance.Contexts;
using Server.Domain.Model.Entity;
using Server.Domain.Repositories;
using Microsoft.EntityFrameworkCore;

namespace Server.Persistance.Repositories
{
    public class DeviceRepository : BaseRepository<DeviceEntity>, IDeviceRepository
    {
        public DeviceRepository (AppDbContext context) : base(context, context.deviceEntities) {}

        public async Task<IEnumerable<DeviceEntity>> listAsync()
        {
            return await context.deviceEntities.ToArrayAsync();
        }

        public Task<DeviceEntity> GetByMac(string mac)
        {   
            if (!string.IsNullOrEmpty(mac)) {
                return context.deviceEntities.FirstOrDefaultAsync(el => el.macAddress.Equals(mac));
            }
            return Task.FromResult<DeviceEntity>(null);
        }
    }
}