using Microsoft.Extensions.DependencyInjection;

using Server.Persistance.Repositories;

namespace Server.Services.Extensions {
    public static class UdpDeviceServiceExtension {
        public static void AddUdpDeviceService(this IServiceCollection services) {
            services.AddSingleton<UdpDeviceService>(new UdpDeviceService(new UdpClient(), services.BuildServiceProvider().GetRequiredService<DeviceRepository>()));
        }
    }
}