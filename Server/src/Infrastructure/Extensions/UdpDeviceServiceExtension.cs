using Microsoft.Extensions.DependencyInjection;

using Server.Interface;
using Server.Application;
using Server.Infrastructure.Services;

namespace Server.Services.Extensions {
    public static class UdpDeviceServiceExtension {
        public static void AddUdpDeviceService(this IServiceCollection services) {
            services.AddSingleton<UdpDeviceInterface>(new UdpDeviceInterface(new UdpService(), services.BuildServiceProvider().GetRequiredService<UdpMessageInterpreter>()));
        }
    }
}