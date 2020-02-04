import { Pipe, PipeTransform } from '@angular/core';
import { DeviceType } from 'src/app/model/values/device-type.enum';

@Pipe({
    name: 'deviceType'
})
export class DeviceTypePipe implements PipeTransform {
    transform(value: DeviceType): string {
        switch (value) {
            case DeviceType.DIODE: return 'Diodes';
            case DeviceType.SOCKET: return 'Sockets';
            case DeviceType.LED: return 'Leds';
            default: return 'other';
        }
    }
}
