import { DeviceType } from 'src/app/model/values/device-type.enum';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';

export interface DeviceCategory {
    type: DeviceType;
    deviceList: Array<DeviceEntity>;
}
