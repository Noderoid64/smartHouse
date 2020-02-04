export class DeviceDto {
    private ip: string;
    private mac: string;
    private name: string;
    private type: string;
    private version: string;
    private paired?: boolean;

    constructor(ip: string, mac: string, name: string, type: string, verison: string) {
        this.ip = ip;
        this.mac = mac;
        this.name = name;
        this.type = type;
        this.version = verison;
    }
}
