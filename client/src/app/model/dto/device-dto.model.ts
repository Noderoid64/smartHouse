export interface DeviceDto {
    ip: string;
    mac: string;
    name: string;
    type: string;
    version: string;
    paired?: boolean;
}
