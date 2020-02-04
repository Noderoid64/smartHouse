import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { DeviceGroupListComponent } from './components/device-group-list/device-group-list.component';
import { HomeRootComponent } from './components/home-root/home-root.component';
import { DeviceCategoriesListComponent } from './components/device-categories-list/device-categories-list.component';
import { HomeRoutingModule} from './home-routing.module';
import { SharedModule } from '@shared/shared.module';
import { AddDeviceDialogComponent } from './components/device-categories-list/add-device-dialog/add-device-dialog.component';


@NgModule({
  declarations: [DeviceGroupListComponent, HomeRootComponent, DeviceCategoriesListComponent, AddDeviceDialogComponent],
  entryComponents: [AddDeviceDialogComponent],
  imports: [
    CommonModule,
    SharedModule,
    HomeRoutingModule
  ]
})
export class HomeModule { }
