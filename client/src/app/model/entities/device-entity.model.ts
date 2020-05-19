import { DeviceType } from '../values/device-type.enum';

export class DeviceEntity {
    constructor(
        public ip: string,
        public mac: string,
        public name: string,
        public type: DeviceType,
        public version: string,
        public paired?: boolean,
    ) {

    }
}
