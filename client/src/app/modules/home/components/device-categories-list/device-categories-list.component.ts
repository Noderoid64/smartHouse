import { Component, OnInit, Input } from '@angular/core';
import { DeviceType} from 'src/app/model/values/device-type.enum';

@Component({
  selector: 'app-device-categories-list',
  templateUrl: './device-categories-list.component.html',
  styleUrls: ['./device-categories-list.component.scss']
})
export class DeviceCategoriesListComponent implements OnInit {

  @Input() private deviceCategories: Array<{type: DeviceType}> | undefined;

  constructor() { }

  ngOnInit() {}

}
