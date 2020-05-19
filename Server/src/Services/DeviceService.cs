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
        private bool _isDebug = Log.IsEnabled(LogEventLevel.Debug);
        private DeviceRepository deviceRepository;

        public DeviceService(DeviceRepository deviceRepository)
        {
            this.deviceRepository = deviceRepository;
        }

        public Task<IEnumerable<DeviceEntity>> asyncList()
        {
            return deviceRepository.listAsync();
        }

        public async Task<bool> persistAsync(DeviceEntity entity)
        {
            bool result = false;
            try
            {
                DeviceEntity entityFromDb = await this.deviceRepository.GetByMac(entity.macAddress);
                if (entityFromDb == null)
                {
                    this.deviceRepository.InsertAsync(entity);
                    this.deviceRepository.SaveAsync();
                    result = true;
                }
                else
                {
                    if (_isDebug) 
                    Log.Debug("entity with mac {0} already exist under {1} id", entity.macAddress, entityFromDb.id);
                }
            }
            catch (Exception e)
            {
                Log.Error(e.Message);
                result = false;
            }
            return result;
        }

        public async Task<IEnumerable<DeviceEntity>> getNewDevices()
        {
            return await this.deviceRepository.getNewDevices();
        }

        public async Task<bool> registerDevice(string mac)
        {
            DeviceEntity entity = await this.deviceRepository.GetByMac(mac);
            bool result = false;
            if (entity != null && entity.isNew == true)
            {
                entity.isNew = false;
                this.deviceRepository.Update(entity);
                this.deviceRepository.Save();
                result = true;
            }
            return result;
        }
    }
}