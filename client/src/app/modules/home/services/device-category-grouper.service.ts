import { Injectable } from '@angular/core';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';
import { DeviceCategory } from '../model/device-category.model';
import { DeviceType } from 'src/app/model/values/device-type.enum';

@Injectable({
  providedIn: 'root'
})
export class DeviceCategoryGrouperService {

  constructor() { }

  public group(devices: Array<DeviceEntity>): Array<DeviceCategory> {
    const result: Map<DeviceType, DeviceCategory> = new Map();
    devices.forEach(device => {
      const deviceItem = result.get(device.type);
      if (!deviceItem) {
        result.set(device.type, { deviceList: [device], type: device.type} as DeviceCategory);
      } else {
        deviceItem.deviceList.push(device);
      }
    });
    return Array.from(result.values());
  }
}
