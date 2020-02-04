import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { LedComponent } from './components/led/led.component';


const routes: Routes = [
  {
    path: 'led/:id',
    component: LedComponent
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class DeviceRoutingModule { }
