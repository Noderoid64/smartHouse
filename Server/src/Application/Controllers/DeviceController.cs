using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

using Server.Application.Dto;
using Server.Model.Entity;
using Server.Services;

using Serilog;
using AutoMapper;

namespace Server.Controllers {
    [ApiController]
    [Route("api/devices")]
    public class DeviceController : Controller {
        private DeviceService deviceService;
        private IMapper mapper;
        public DeviceController(DeviceService deviceService, IMapper mapper) {
            this.deviceService = deviceService;
            this.mapper = mapper;
        }

        [HttpGet]
        public async Task<IEnumerable<DeviceDto>> GetAllAsync() {
            return mapper.Map<IEnumerable<DeviceEntity>,IEnumerable<DeviceDto>>(await this.deviceService.asyncList());
        }

        [HttpGet("new")]
        public async Task<IEnumerable<DeviceDto>> GetNewAsync() {
            return mapper.Map<IEnumerable<DeviceEntity>,IEnumerable<DeviceDto>>(await this.deviceService.getNewDevices());
        }

        [HttpPost("register/{mac}")]
        public async Task<bool> registerDevice(string mac) {
            return await this.deviceService.registerDevice(mac);
        }
    }
}