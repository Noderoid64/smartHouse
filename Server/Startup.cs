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
using AutoMapper;

using Server.Tools.Middleware;
using Server.Application.Mappers;
using Server.Persistance.Contexts;
using Server.Infrastructure.Persistance;
using Server.Infrastructure.Assemblers;
using Server.Application;
using Server.Services.Extensions;

namespace Server
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // Add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddControllers();
            services.AddDbContext<AppDbContext>(options => options.UseNpgsql(Configuration.GetConnectionString("smartDb")));
            
            // Infrastructure
            services.AddScoped<DeviceRepository>();
            services.AddScoped<DeviceAssembler>();
            services.AddScoped<UdpMessageAssembler>();
            // Domain
            // Application
            services.AddScoped<DeviceService>();
            services.AddScoped<UdpMessageInterpreter>();
            // Interface
            services.AddUdpDeviceService();
            
    
            
            
            
            
            
            services.AddAutoMapper(typeof(DeviceMapper));
            services.AddCors();
        }

        // Configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env, ILoggerFactory loggerFactory)
        {
            app.UseMiddleware<LogMiddleware>();
            app.UseCors(e => e.AllowAnyHeader().AllowAnyMethod().AllowAnyOrigin());
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
