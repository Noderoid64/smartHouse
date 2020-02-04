import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { DeviceDto } from 'src/app/model/dto/device-dto.model';
import { Observable } from 'rxjs';
import { map} from 'rxjs/operators';
import { environment } from 'src/environments/environment';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';

@Injectable({
    providedIn: 'root'
})
export class DeviceWebService {
    private readonly url = environment.serverUrl + 'devices/';

    public constructor(private httpClient: HttpClient) {

    }

    public getDevices(): Observable<DeviceEntity[]> {
        return this.httpClient.get(this.url).pipe(map((e) => {
            return (e as DeviceDto[]).map(item => this.assembleDeviceEntity(item));
        }));
    }

    private assembleDeviceEntity(dto: DeviceDto) {
        return new DeviceEntity(
            dto.ip,
            dto.mac,
            dto.name,
            dto.type,
            dto.version,
            dto.paired
        );
    }
}
