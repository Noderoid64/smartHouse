import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IonicModule } from '@ionic/angular';
import { HomeRoutingModule} from './home-routing.module';
import { HomePageComponent } from './components/home-page/home-page.component';


@NgModule({
  declarations: [
    HomePageComponent
  ],
  imports: [
    CommonModule,
    IonicModule,
    HomeRoutingModule
  ]
})
export class HomeModule { }
