import { Injectable } from '@angular/core';
import { MatSnackBar } from '@angular/material';

@Injectable({providedIn: 'root'})
export class TooltipService {

    constructor(private snackBar: MatSnackBar) {

    }

    public showInfo(message: string) {
        this.snackBar.open(message, 'ok', {
            horizontalPosition: 'right',
            verticalPosition: 'bottom',
            duration: 4000
        });
    }
}
