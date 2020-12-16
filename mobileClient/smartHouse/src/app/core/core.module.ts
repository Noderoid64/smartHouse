import { NgModule } from '@angular/core';
import { TabsComponent } from './tabs/tabs.component';
import { SharedModule } from '../shared/shared.module';

@NgModule({
    imports: [
        SharedModule
    ],
    exports: [
        TabsComponent
    ],
    declarations: [
        TabsComponent
    ],
    providers: [],
})
export class CoreModule { }
