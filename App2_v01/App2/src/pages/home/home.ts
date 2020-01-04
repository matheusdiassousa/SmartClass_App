import { Component, ViewChild } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';

import { SuperTabs } from 'ionic2-super-tabs';
import { AlertController } from 'ionic-angular/components/alert/alert-controller';

@IonicPage()
@Component({
  selector: 'page-home',
  templateUrl: 'home.html',
})
export class HomePage {
 
  pages = [
    { pageName: 'ControlPage', title: 'Controle', icon: 'game-controller-a', id: 'ControleTab'},
    { pageName: 'InicioPage', title: 'Início', icon: 'home', id: 'InícioTab'},
    { pageName: 'AboutPage', title: 'Sobre', icon: 'man', id: 'SobreTab'}
  ];
 
  
 
  @ViewChild(SuperTabs) superTabs: SuperTabs;
 
  constructor(public navCtrl: NavController, public navParams: NavParams, private alertCtrl: AlertController) { }
 
  
 
}