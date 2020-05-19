import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';
import { MatDialog } from '@angular/material';
import { AddDeviceDialogComponent } from './add-device-dialog/add-device-dialog.component';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';

@Component({
  selector: 'app-device-list',
  templateUrl: './device-list.component.html',
  styleUrls: ['./device-list.component.scss']
})
export class DeviceListComponent implements OnInit {

  @Input() public devices: DeviceEntity[] = [];

  @Output() addDevice = new EventEmitter<string>();

  constructor(public dialog: MatDialog) { }

  ngOnInit() {}

  public onAddButtonClick() {
    const dialogRef = this.dialog.open(AddDeviceDialogComponent, {});
    dialogRef.afterClosed().subscribe((result: string) => {
      this.addDevice.emit(result);
    });
  }
}
