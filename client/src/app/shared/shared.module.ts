import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HeaderComponent } from './components/header/header.component';

import {
  MatIconModule,
  MatButtonModule,
  MatCardModule,
  MatDialogModule,
  MatTableModule
} from '@angular/material';

import { DeviceItemComponent } from './components/device-item/device-item.component';

import { DeviceTypePipe} from './pipes/device-type.pipe';

@NgModule({
  declarations: [HeaderComponent, DeviceItemComponent, DeviceTypePipe],
  imports: [
    CommonModule,
    MatIconModule,
    MatButtonModule,
    MatCardModule,
    MatDialogModule,
    MatTableModule
  ],
  exports: [
    HeaderComponent,
    DeviceItemComponent,

    DeviceTypePipe,

    MatIconModule,
    MatButtonModule,
    MatCardModule,
    MatDialogModule,
    MatTableModule
  ]
})
export class SharedModule { }
