import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { BluetoothSerial } from '@ionic-native/bluetooth-serial';
import { AlertController } from 'ionic-angular';

import { HomePage } from './../home/home';
import { InicioPage } from './../inicio/inicio';

@IonicPage()
@Component({
  selector: 'page-bt',
  templateUrl: 'bt.html',
})
export class BtPage {

	unpairedDevices: any; //Variável para dispostivos não armazenados, pode receber qualquer tipo de dado
	pairedDevices: any; //Variável que vai armazenar dispositivos pareados
	gettingDevices: Boolean; //


	  constructor(public navCtrl: NavController, public navParams: NavParams, public bluetoothSerial: BluetoothSerial, public alertCtrl: AlertController) {
	  	bluetoothSerial.enable();
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad BtPage');
  }

  startScanning() {
    this.pairedDevices = null;
    this.unpairedDevices = null;
    this.gettingDevices = true;
    this.bluetoothSerial.discoverUnpaired().then((success) => {
      this.unpairedDevices = success;
      this.gettingDevices = false;
      success.forEach(element => {
        // alert(element.name);
      });
    },
      (err) => {
        console.log(err);
      })

    /*this.bluetoothSerial.list().then((success) => {
      this.pairedDevices = success;
    },
      (err) => {

      })*/
  }
  success = (data) => alert("Conectado!");
  fail = (error) => alert(error);

  selectDevice(address: any) {

    let alert = this.alertCtrl.create({
      title: 'Conectar',
      message: 'Deseja conectar-se a este dispositivo?',
      buttons: [
        {
          text: 'Cancelar',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Conectar',
          handler: () => {
            this.bluetoothSerial.connect(address).subscribe(this.success, this.fail);
          }
        }
      ]
    });
    alert.present();

  }

  disconnect() {
    let alert = this.alertCtrl.create({
      title: 'Desconectar?',
      message: 'Deseja desconectar?',
      buttons: [
        {
          text: 'Cancelar',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Desconectar',
          handler: () => {
            this.bluetoothSerial.disconnect();
          }
        }
      ]
    });
    alert.present();
  }

    pushPage(): void {
      this.navCtrl.push(HomePage);
    }

  
}




