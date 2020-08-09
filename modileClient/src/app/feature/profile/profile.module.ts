import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IonicModule } from '@ionic/angular';
import { ProfileRoutingModule } from './profile-routing.module';
import { ProfileRootComponent } from './components/profile-root/profile-root.component';

@NgModule({
  declarations: [
    ProfileRootComponent
  ],
  imports: [
    CommonModule,
    IonicModule,
    ProfileRoutingModule
  ]
})
export class ProfileModule { }
