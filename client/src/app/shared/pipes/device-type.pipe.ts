import { Pipe, PipeTransform } from '@angular/core';
import { DeviceType } from 'src/app/model/values/device-type.enum';

@Pipe({
    name: 'deviceType'
})
export class DeviceTypePipe implements PipeTransform {
    transform(value: DeviceType): string {
        switch (value) {
            case DeviceType.DIODE: return 'Diode';
            case DeviceType.SOCKET: return 'Socket';
            case DeviceType.LED: return 'Led';
            default: return 'Other';
        }
    }
}
