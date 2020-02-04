import { Component, Input } from '@angular/core';
import { DeviceType } from 'src/app/model/values/device-type.enum';

@Component({
  selector: 'app-device-item',
  templateUrl: './device-item.component.html',
  styleUrls: ['./device-item.component.scss']
})
export class DeviceItemComponent {

  @Input() public type: DeviceType | undefined;
  @Input() public label: string | undefined;
  @Input() public count = 0;

  public deviceType = DeviceType;

  constructor() { }

}
