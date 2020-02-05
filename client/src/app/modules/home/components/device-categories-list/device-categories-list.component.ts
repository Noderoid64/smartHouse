import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';
import { MatDialog } from '@angular/material';
import { DeviceCategory } from '../../model/device-category.model';
import { AddDeviceDialogComponent } from './add-device-dialog/add-device-dialog.component';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-device-categories-list',
  templateUrl: './device-categories-list.component.html',
  styleUrls: ['./device-categories-list.component.scss']
})
export class DeviceCategoriesListComponent implements OnInit {

  @Input() public deviceCategories$: Observable<DeviceCategory[]> | undefined;
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
