import { Component } from '@angular/core';

import { Plugins, Modals } from "@capacitor/core";
const { UdpPlugin } = Plugins;
import {UdpPluginUtils} from "capacitor-udp";
import { async } from '@angular/core/testing';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  constructor() {
    setTimeout( async () => {
      await UdpPlugin.closeAllSockets();
      let info = await UdpPlugin.create();
      UdpPlugin.bind({socketId: info.socketId, address: info.ipv4, port: 4096});
      console.log(info);
      UdpPlugin.addListener('receive', (message) => {
        Modals.alert({title: 'UPD', message: message.buffer});
      })
    },500);
  }

}
