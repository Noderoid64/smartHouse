using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Server.Domain.Model.Entity;
using Server.Domain.Services;
using Server.Domain.Repositories;

using Serilog;
using Serilog.Events;

namespace Server.Services
{
    public class DeviceService : IDeviceService
    {
        private IDeviceRepository deviceRepository;

        public DeviceService(IDeviceRepository deviceRepository)
        {
            this.deviceRepository = deviceRepository;
        }
        public Task<IEnumerable<DeviceEntity>> asyncList()
        {
            return deviceRepository.listAsync();
        }

        public async void persistAsync(DeviceEntity entity)
        {
            DeviceEntity entityFromDb = await this.deviceRepository.GetByMac(entity.macAddress);

            if (entityFromDb == null)
            {
                this.deviceRepository.Insert(entity);
                this.deviceRepository.Save();
            }
            else
            {
                if (Log.IsEnabled(LogEventLevel.Debug))
                {
                    Log.Debug("entity from db.id = " + entityFromDb.id);
                }
            }
        }
    }
}