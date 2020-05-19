import { Injectable } from '@angular/core';
import { DeviceEntity } from '../model/entities/device-entity.model';
import { DeviceDto } from '../model/dto/device-dto.model';
import { DeviceType } from '../model/values/device-type.enum';

@Injectable({providedIn: 'root'})
export class DeviceAssemblerService {
    public assemble(dto: DeviceDto): DeviceEntity {
        let type: DeviceType;
        switch (dto.type) {
            case 'SOCKET': type = DeviceType.SOCKET; break;
            case 'DIODE': type = DeviceType.DIODE; break;
            case 'LED': type = DeviceType.LED; break;
            default: type = DeviceType.OTHER; break;
        }
        return new DeviceEntity(
            dto.ip,
            dto.mac,
            dto.name,
            type,
            dto.version,
            dto.paired
        );
    }
}