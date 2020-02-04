using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Server.Services;
using Server.Model.Entity;

using Serilog;

namespace Server.Controllers {
    [ApiController]
    [Route("api/devices")]
    public class DeviceController : Controller {
        private DeviceService deviceService;

        public DeviceController(DeviceService deviceService) {
            this.deviceService = deviceService;
        }

        [HttpGet]
        public async Task<IEnumerable<DeviceEntity>> GetAllAsync() {
            return await this.deviceService.asyncList();
        }

        [HttpGet("new")]
        public async Task<IEnumerable<DeviceEntity>> GetNewAsync() {
            return await this.deviceService.getNewDevices();
        }
    }
}