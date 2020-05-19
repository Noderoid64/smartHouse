using AutoMapper;

using Server.Model.Entity;
using Server.Application.Dto;

namespace Server.Application.Mappers {
    public class DeviceMapper : Profile {
        public DeviceMapper() {
            CreateMap<DeviceEntity, DeviceDto>()
            .ForMember(d => d.ip, e => e.MapFrom(s =>s.ipAddress))
            .ForMember(d => d.mac, e => e.MapFrom(s => s.macAddress));
        }
    }
}