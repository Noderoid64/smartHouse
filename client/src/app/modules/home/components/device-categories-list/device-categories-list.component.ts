import { Component, OnInit, Input } from '@angular/core';
import { DeviceType} from 'src/app/model/values/device-type.enum';
import { MatDialog } from '@angular/material';
import { AddDeviceDialogComponent } from './add-device-dialog/add-device-dialog.component';

@Component({
  selector: 'app-device-categories-list',
  templateUrl: './device-categories-list.component.html',
  styleUrls: ['./device-categories-list.component.scss']
})
export class DeviceCategoriesListComponent implements OnInit {

  @Input() public deviceCategories: Array<{type: DeviceType, count?: number}> | undefined =
  [{type: DeviceType.SOCKET, count: 5}, {type: DeviceType.DIODE}];

  constructor(public dialog: MatDialog) { }

  ngOnInit() {}

  public onAddButtonClick() {
    const dialogRef = this.dialog.open(AddDeviceDialogComponent, {
      width: '250px'
    });
  }
}
