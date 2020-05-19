import { Component, OnInit, OnDestroy } from '@angular/core';
import { DeviceWebService } from 'src/app/services/web/device-web.service';
import { TooltipService } from 'src/app/services/tooltip.service';
import { environment } from 'src/environments/environment';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';

@Component({
  selector: 'app-home-root',
  templateUrl: './home-root.component.html',
  styleUrls: ['./home-root.component.scss']
})
export class HomeRootComponent implements OnInit, OnDestroy {

  public devices: DeviceEntity[] = [];

  private intervalId: any;

  constructor(
    private deviceWebService: DeviceWebService,
    private tooltipService: TooltipService) {
    this.loadCategories();
    this.startDeviceListUpdate();
  }

  ngOnInit() {
  }

  ngOnDestroy() {
    clearInterval(this.intervalId);
  }

  public onAddDevice(mac: string) {
    this.deviceWebService.addNewDevice(mac).subscribe(e => {
      if (e === true) {
        this.tooltipService.showInfo('Device has been added');
      }
    });
  }

  private loadCategories(): void {
    this.deviceWebService.getDevices().subscribe(el => {
      this.devices = el;
    });
  }

  private startDeviceListUpdate(): void {
    this.intervalId = setInterval(() => {
      this.loadCategories();
    }, environment.deviceCategoriesUpdatePeriod);
  }

}
