import { NgModule } from '@angular/core';

import { IonicModule } from '@ionic/angular';

const reExport = [
    IonicModule
]

@NgModule({
    imports: [
        ...reExport
    ],
    exports: [
        ...reExport
    ],
    declarations: [],
    providers: [],
})
export class SharedModule { }
