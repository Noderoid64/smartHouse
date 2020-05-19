import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { SharedModule } from '@shared/shared.module';
import { HomeRoutingModule } from './home-routing.module';
import { DeviceGroupListComponent } from './components/home/device-group-list/device-group-list.component';
import { HomeRootComponent} from './components/home/home-root/home-root.component';
import { DeviceListComponent } from './components/home/device-list/device-list.component';
import { AddDeviceDialogComponent } from './components/home/device-list/add-device-dialog/add-device-dialog.component';
import { SocketRootComponent } from './components/device-pages/socket/socket-root/socket-root.component';


@NgModule({
  declarations: [
    DeviceGroupListComponent,
    HomeRootComponent,
    DeviceListComponent,
    AddDeviceDialogComponent,
    SocketRootComponent
  ],
  entryComponents: [
    AddDeviceDialogComponent
  ],
  imports: [
    CommonModule,
    SharedModule,
    HomeRoutingModule
  ]
})
export class HomeModule { }
