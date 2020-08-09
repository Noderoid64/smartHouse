import { IonicModule } from '@ionic/angular';
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { MenuRoutingModule } from './menu-routing.module';

import { MenuPage } from './menu.page';

@NgModule({
  imports: [
    IonicModule,
    CommonModule,
    FormsModule,
    MenuRoutingModule
  ],
  declarations: [MenuPage]
})
export class MenuModule {}
