import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { DeviceDto } from 'src/app/model/dto/device-dto.model';
import { Observable } from 'rxjs';
import { map} from 'rxjs/operators';
import { environment } from 'src/environments/environment';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';
import { DeviceAssemblerService } from '../device-assembler.service';

@Injectable({
    providedIn: 'root'
})
export class DeviceWebService {
    private readonly url = environment.serverUrl + 'devices/';

    public constructor(private httpClient: HttpClient, private deviceAssembler: DeviceAssemblerService) {

    }

    public getDevices(): Observable<DeviceEntity[]> {
        return this.httpClient.get(this.url).pipe(map((e) => {
            return (e as DeviceDto[]).map(item => this.deviceAssembler.assemble(item));
        }));
    }

    public getNewDevices(): Observable<DeviceEntity[]> {
        return this.httpClient.get(this.url + 'new').pipe(map(e => {
            return (e as DeviceDto[]).map(item => this.deviceAssembler.assemble(item));
        }));
    }

    public addNewDevice(mac: string): Observable<boolean> {
        return this. httpClient.post(this.url + 'register/' + mac, {}).pipe(map(e => e as boolean));
    }
}
