import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { AlertController } from 'ionic-angular';
import { BluetoothSerial } from '@ionic-native/bluetooth-serial';

import { BtPage } from './../bt/bt';



@IonicPage()
@Component({
  selector: 'page-inicio',
  templateUrl: 'inicio.html',
})
export class InicioPage {

  constructor(public navCtrl: NavController, public navParams: NavParams, public alertCtrl: AlertController, public bluetoothSerial: BluetoothSerial) {
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad InicioPage');
  }

  pushPage(): void {
		this.navCtrl.push(BtPage);
  	}

  	destravarFechadura(): void {
  		this.bluetoothSerial.write('q');
  	}
	
	


}

