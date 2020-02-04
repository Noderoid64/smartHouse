export class DeviceEntity {
    constructor(
        public ip: string,
        public mac: string,
        public name: string,
        public type: string,
        public version: string,
        public paired?: boolean,
    ) {

    }
}
