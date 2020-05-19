import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, ParamMap } from '@angular/router';
import { switchMap, map } from 'rxjs/operators';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-socket-root',
  templateUrl: './socket-root.component.html',
  styleUrls: ['./socket-root.component.scss']
})
export class SocketRootComponent implements OnInit {

  public ip: string | null = '';
  public status = false;

  constructor(private route: ActivatedRoute, private http: HttpClient) { }

  ngOnInit() {
    this.ip = this.route.snapshot.params.ip;
    console.log(this.route.snapshot.params.ip);
  }

  public onClick() {
    if (this.status) {
      this.http.get('http://' + this.ip + '/turn-off').subscribe(el => console.log(el));
      this.status = false;
    } else {
      this.http.get('http://' + this.ip + '/turn-on').subscribe(el => console.log(el));
      this.status = true;
    }
  }
}
