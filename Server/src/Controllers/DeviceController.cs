using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Server.Domain.Services;
using Server.Domain.Model.Entity;

using Serilog;

namespace Server.Controllers {
    [ApiController]
    [Route("api/device")]
    public class DeviceController : Controller {
        private IDeviceService deviceService;

        public DeviceController(IDeviceService deviceService) {
            this.deviceService = deviceService;
        }

        [HttpGet]
        public async Task<IEnumerable<DeviceEntity>> GetAllAsync() {
            Log.Debug("asdfff");
            return await this.deviceService.asyncList();
        }
    }
}