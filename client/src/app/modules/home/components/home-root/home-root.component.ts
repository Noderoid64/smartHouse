import { Component, OnInit } from '@angular/core';
import { DeviceWebService } from 'src/app/services/web/device-web.service';
import { Observable } from 'rxjs';
import { DeviceCategory } from '../../model/device-category.model';
import { map } from 'rxjs/operators';
import { DeviceCategoryGrouperService } from '../../services/device-category-grouper.service';

@Component({
  selector: 'app-home-root',
  templateUrl: './home-root.component.html',
  styleUrls: ['./home-root.component.scss']
})
export class HomeRootComponent implements OnInit {

  public deviceCategories$: Observable<DeviceCategory[]> | undefined;

  constructor(private deviceWebService: DeviceWebService, private deviceCategoryGrouper: DeviceCategoryGrouperService) {
    this.loadCategories();
  }

  ngOnInit() {
  }

  public onAddDevice(mac: string) {
    this.deviceWebService.addNewDevice(mac).subscribe(e => {
      if (e === true) {
        this.loadCategories();
      }
    });
  }

  private loadCategories(): void {
    this.deviceCategories$ = this.deviceWebService.getDevices().pipe(map (e => this.deviceCategoryGrouper.group(e)));
  }

}
