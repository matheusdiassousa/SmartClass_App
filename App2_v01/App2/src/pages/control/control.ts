import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { BluetoothSerial } from '@ionic-native/bluetooth-serial';

//import { BtPage } from './../bt/bt';
/**
 * Generated class for the ControlPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-control',
  templateUrl: 'control.html',
})
export class ControlPage {

  constructor(public navCtrl: NavController, public navParams: NavParams, public bluetoothSerial: BluetoothSerial) {
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad ControlPage');
  }

  lamp1(): void {
  		this.bluetoothSerial.write('e');
  }

  lamp2(): void {
  		this.bluetoothSerial.write('r');
  }

  lamp3(): void {
  		this.bluetoothSerial.write('t');
  }

  ligarDS(): void {
  		this.bluetoothSerial.write('w');
  }
  
  ligarC1(): void {
      this.bluetoothSerial.write('y');
  }
  desligarC1(): void {
      this.bluetoothSerial.write('u');
  }
  temp18C1(): void {
      this.bluetoothSerial.write('i');
  }
  
  temp19C1(): void {
      this.bluetoothSerial.write('o');
  }
  temp20C1(): void {
      this.bluetoothSerial.write('p');
  }
  temp21C1(): void {
      this.bluetoothSerial.write('a');
  }

  ligarC2(): void {
      this.bluetoothSerial.write('s');
  }
  desligarC2(): void {
      this.bluetoothSerial.write('d');
  }
  temp18C2(): void {
      this.bluetoothSerial.write('f');
  }
  
  temp19C2(): void {
      this.bluetoothSerial.write('g');
  }
  temp20C2(): void {
      this.bluetoothSerial.write('h');
  }
  temp21C2(): void {
      this.bluetoothSerial.write('i');
  }      


}
