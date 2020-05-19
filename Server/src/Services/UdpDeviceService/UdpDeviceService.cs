using System.Net;
using System;
using Server.Model.Entity;
using Server.Model.Value;
using Server.Services;
using Server.Persistance.Repositories;
using Server.Services.UdpDeviceServices;

using Serilog;
using Serilog.Events;

namespace Server.Services
{
    public class UdpDeviceService
    {
        private UdpClient client;
        private DeviceRepository deviceRepository;
        private DeviceEntityFactory factory;

        public UdpDeviceService(UdpClient client, DeviceRepository deviceRepository)
        {
            this.client = client;
            this.deviceRepository = deviceRepository;
            this.factory = new DeviceEntityFactory();

            this.client.receive += onReceive;
        }

        private void onReceive(string message, IPEndPoint source)
        {
            if (Log.IsEnabled(LogEventLevel.Information))
            {
                Log.Information("onReceive: " + message + " " + source.Address + ":" + source.Port);
            }
            DeviceEntity entity = factory.build(message, source);
            if (entity != null)
            {
                if (entity.type == DeviceType.CLIENT) {
                    handleClient();
                } else if (entity.type != DeviceType.MANAGED_SERVER) {
                    handleDeviceAsync(entity);
                }
                
            }
        }

        private void handleClient() {
            client.sendMulticastAsync(String.Format("|{0}|{1}", DeviceType.MANAGED_SERVER, new DeviceVersion("0.0.1")));
        }

        private async void handleDeviceAsync(DeviceEntity entity)  {
            DeviceEntity entityFromDb = await deviceRepository.GetByMac(entity.macAddress);
                if (entityFromDb != null)
                {
                    entityFromDb.ipAddress = entity.ipAddress;
                    entityFromDb.lastPing = DateTime.Now;
                    deviceRepository.Update(entityFromDb);
                    deviceRepository.Save();
                }
                else
                {
                    deviceRepository.Insert(entity);
                    deviceRepository.Save();
                }
        }
    }
}