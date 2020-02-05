using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Server.Model.Entity;
using Server.Services;
using Server.Persistance.Repositories;

using Serilog;
using Serilog.Events;

namespace Server.Services
{
    public class DeviceService
    {
        private DeviceRepository deviceRepository;

        public DeviceService(DeviceRepository deviceRepository)
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

        public async Task<IEnumerable<DeviceEntity>> getNewDevices() {
            return await this.deviceRepository.getNewDevices();
        }

        public async Task<bool> registerDevice(string mac) {
            DeviceEntity entity = await this.deviceRepository.GetByMac(mac);
            bool result = false;
            if (entity != null && entity.isNew == true) {
                entity.isNew = false;
                this.deviceRepository.Update(entity);
                this.deviceRepository.Save();
                result = true;
            }
            return result;
        }
    }
}