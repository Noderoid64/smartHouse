import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { DeviceDto } from 'src/app/model/dto/device-dto.model';

@Injectable({
    providedIn: 'root'
})
export class DeviceWebService {
    private readonly url = 'api/devices/';

    public constructor(private httpClient: HttpClient) {

    }

    public getDevices(): Promise<DeviceDto> {
        return 
    }
}
