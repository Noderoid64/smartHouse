import { Component, OnInit, Inject } from '@angular/core';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material';
import { DeviceWebService } from 'src/app/services/web/device-web.service';
import { Observable } from 'rxjs';
import { DeviceEntity } from 'src/app/model/entities/device-entity.model';

@Component({
  selector: 'app-add-device-dialog',
  templateUrl: './add-device-dialog.component.html',
  styleUrls: ['./add-device-dialog.component.scss']
})
export class AddDeviceDialogComponent implements OnInit {

  public newDevices$: Observable<DeviceEntity[]>;

  constructor(
    public dialogRef: MatDialogRef<AddDeviceDialogComponent>,
    @Inject(MAT_DIALOG_DATA) public data: any,
    private deviceWebService: DeviceWebService
  ) {
    this.newDevices$ = this.deviceWebService.getNewDevices();
  }

  ngOnInit() {}

  public onDeviceClick(mac: string) {
    this.dialogRef.close(mac);
  }
}
