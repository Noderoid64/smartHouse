using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.EntityFrameworkCore;
using Serilog;

using Server.Persistance.Contexts;
using Server.Persistance.Repositories;
using Server.Services;
using Server.Domain.Repositories;
using Server.Domain.Services;

namespace Server
{
    public class Startup
    {
        public Startup(IConfiguration configuration) {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // Add services to the container.
        public void ConfigureServices(IServiceCollection services) {
            services.AddControllers();
            services.AddDbContext<AppDbContext>(options => options.UseNpgsql("Host=localhost;Database=smartDb;Username=postgres;Password=qwertyui"));
            services.AddScoped<IDeviceRepository, DeviceRepository>();
            services.AddScoped<IDeviceService, DeviceService>();
            IUdpClient udpClient = new UdpClient();
            services.AddSingleton<IUdpDeviceService>(new UdpDeviceService(udpClient, services.BuildServiceProvider().GetRequiredService<IDeviceRepository>()));
        }

        // Configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env, ILoggerFactory loggerFactory) {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            app.UseHttpsRedirection();
            app.UseRouting();
            app.UseAuthorization();
            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllers();
            });
        }
    }
}
