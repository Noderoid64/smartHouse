using System.Net;
using Server.Domain.Model.Entity;
using Server.Domain.Services;
using Server.Domain.Repositories;
using Server.Services.UdpDeviceServices;

using Serilog;
using Serilog.Events;

namespace Server.Services {
    public class UdpDeviceService : IUdpDeviceService
    {
        private IUdpClient client;
        private IDeviceRepository deviceRepository;
        private DeviceEntityFactory factory;

        public UdpDeviceService (IUdpClient client, IDeviceRepository deviceRepository) {
            this.client = client;
            this.deviceRepository = deviceRepository;
            this.factory = new DeviceEntityFactory();

            this.client.receive += onReceive;
        }
        public void scanDevices()
        {
            this.client.sendMulticastAsync("Hello");
        }

        private async void onReceive(string message, IPEndPoint source) {
            if (Log.IsEnabled(LogEventLevel.Information)) {
                Log.Information("onReceive: " + message + " " + source.Address + ":" + source.Port);
            }
            DeviceEntity entity = factory.build(message, source);
            DeviceEntity entityFromDb = await deviceRepository.GetByMac(entity.macAddress);
            if (entityFromDb != null) {
                entityFromDb.ipAddress = entity.ipAddress;
                deviceRepository.Update(entityFromDb);
                deviceRepository.Save();
            } else {
                deviceRepository.Insert(entity);
                deviceRepository.Save();
            }
        }
    }
}