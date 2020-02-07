import { Component, OnInit, OnDestroy } from '@angular/core';
import { DeviceWebService } from 'src/app/services/web/device-web.service';
import { Observable } from 'rxjs';
import { DeviceCategory } from '../../model/device-category.model';
import { map } from 'rxjs/operators';
import { DeviceCategoryGrouperService } from '../../services/device-category-grouper.service';
import { TooltipService } from 'src/app/services/tooltip.service';
import { environment } from 'src/environments/environment';

@Component({
  selector: 'app-home-root',
  templateUrl: './home-root.component.html',
  styleUrls: ['./home-root.component.scss']
})
export class HomeRootComponent implements OnInit, OnDestroy {

  public deviceCategories: DeviceCategory[] = [];

  private intervalId: any;

  constructor(
    private deviceWebService: DeviceWebService,
    private deviceCategoryGrouper: DeviceCategoryGrouperService,
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
    this.deviceWebService.getDevices().pipe(map(e => this.deviceCategoryGrouper.group(e))).subscribe(el => {
      this.deviceCategories = el;
    });
  }

  private startDeviceListUpdate(): void {
    this.intervalId = setInterval(() => {
      this.loadCategories();
    }, environment.deviceCategoriesUpdatePeriod);
  }

}
