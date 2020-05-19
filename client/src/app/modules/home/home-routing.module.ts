import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeRootComponent } from './components/home/home-root/home-root.component';
import { SocketRootComponent } from './components/device-pages/socket/socket-root/socket-root.component';


const routes: Routes = [
  {
    path: '', component: HomeRootComponent
  }, {
    path: 'device/socket/:ip', component: SocketRootComponent
  }, {
    path: '**',
    redirectTo: ''
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class HomeRoutingModule { }
