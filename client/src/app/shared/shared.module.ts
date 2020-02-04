import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HeaderComponent } from './components/header/header.component';

import {
  MatIconModule,
  MatButtonModule
} from '@angular/material';

@NgModule({
  declarations: [HeaderComponent],
  imports: [
    CommonModule,
    MatIconModule,
    MatButtonModule
  ],
  exports: [
    HeaderComponent,
    MatIconModule,
    MatButtonModule
  ]
})
export class SharedModule { }
