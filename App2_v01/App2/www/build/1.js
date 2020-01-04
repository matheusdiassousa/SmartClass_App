webpackJsonp([1],{

/***/ 291:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "ControlPageModule", function() { return ControlPageModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_ionic_angular__ = __webpack_require__(15);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__control__ = __webpack_require__(295);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};



var ControlPageModule = /** @class */ (function () {
    function ControlPageModule() {
    }
    ControlPageModule = __decorate([
        Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["I" /* NgModule */])({
            declarations: [
                __WEBPACK_IMPORTED_MODULE_2__control__["a" /* ControlPage */],
            ],
            imports: [
                __WEBPACK_IMPORTED_MODULE_1_ionic_angular__["j" /* IonicPageModule */].forChild(__WEBPACK_IMPORTED_MODULE_2__control__["a" /* ControlPage */]),
            ],
        })
    ], ControlPageModule);
    return ControlPageModule;
}());

//# sourceMappingURL=control.module.js.map

/***/ }),

/***/ 295:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return ControlPage; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_ionic_angular__ = __webpack_require__(15);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ionic_native_bluetooth_serial__ = __webpack_require__(104);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



//import { BtPage } from './../bt/bt';
/**
 * Generated class for the ControlPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */
var ControlPage = /** @class */ (function () {
    function ControlPage(navCtrl, navParams, bluetoothSerial) {
        this.navCtrl = navCtrl;
        this.navParams = navParams;
        this.bluetoothSerial = bluetoothSerial;
    }
    ControlPage.prototype.ionViewDidLoad = function () {
        console.log('ionViewDidLoad ControlPage');
    };
    ControlPage.prototype.lamp1 = function () {
        this.bluetoothSerial.write('e');
    };
    ControlPage.prototype.lamp2 = function () {
        this.bluetoothSerial.write('r');
    };
    ControlPage.prototype.lamp3 = function () {
        this.bluetoothSerial.write('t');
    };
    ControlPage.prototype.ligarDS = function () {
        this.bluetoothSerial.write('w');
    };
    ControlPage.prototype.ligarC1 = function () {
        this.bluetoothSerial.write('y');
    };
    ControlPage.prototype.desligarC1 = function () {
        this.bluetoothSerial.write('u');
    };
    ControlPage.prototype.temp18C1 = function () {
        this.bluetoothSerial.write('i');
    };
    ControlPage.prototype.temp19C1 = function () {
        this.bluetoothSerial.write('o');
    };
    ControlPage.prototype.temp20C1 = function () {
        this.bluetoothSerial.write('p');
    };
    ControlPage.prototype.temp21C1 = function () {
        this.bluetoothSerial.write('a');
    };
    ControlPage.prototype.ligarC2 = function () {
        this.bluetoothSerial.write('s');
    };
    ControlPage.prototype.desligarC2 = function () {
        this.bluetoothSerial.write('d');
    };
    ControlPage.prototype.temp18C2 = function () {
        this.bluetoothSerial.write('f');
    };
    ControlPage.prototype.temp19C2 = function () {
        this.bluetoothSerial.write('g');
    };
    ControlPage.prototype.temp20C2 = function () {
        this.bluetoothSerial.write('h');
    };
    ControlPage.prototype.temp21C2 = function () {
        this.bluetoothSerial.write('i');
    };
    ControlPage = __decorate([
        Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
            selector: 'page-control',template:/*ion-inline-start:"C:\Users\mathe\Google Drive\TCC2\AppTCC\App2_v01\App2\src\pages\control\control.html"*/'<!--\n  Generated template for the ControlPage page.\n\n  See http://ionicframework.com/docs/components/#navigation for more info on\n  Ionic pages and navigation.\n-->\n\n\n<ion-content padding class=\'content\'>\n	\n	<!-- <ion-list-header class="titulo">Iluminação</ion-list-header> -->\n		<div class="titulo">Iluminação</div>\n		<div class=\'container\'>\n			<div class="div-botao">	\n				<button  class=\'botao\' icon-start (click)="lamp1()">\n				<ion-icon name="bulb" class=\'icon-size-ilu\'></ion-icon><p>Frente</p>\n				</button>\n			</div>\n			\n			<div class="div-botao">\n				<button class=\'botao\' icon-start (click)="lamp2()">\n				<ion-icon name="bulb" class=\'icon-size-ilu\'></ion-icon><p>Meio</p>\n				</button>\n			</div>	\n			\n			<div class="div-botao">\n				<button class=\'botao\' icon-start (click)="lamp3()">\n				<ion-icon name="bulb" class=\'icon-size-ilu\'></ion-icon><p>Fundo</p>\n				</button>\n			</div>\n		</div>\n\n		<div class="titulo">Central de Ar 1</div>\n		<div class=\'container_1\'>\n			<div class="div-botao_ar_big">	\n				<button  class=\'botao_ar\' icon-start (click)="ligarC1()">\n				<ion-icon name="snow" class=\'icon_size\'></ion-icon><p class="text-ar">Ligar</p>\n				</button>\n			</div>\n			\n			<div class="div-botao_ar_big">\n				<button class=\'botao_ar\' icon-start (click)="desligarC1()">\n				<ion-icon name="snow" class=\'icon_size\'></ion-icon><p class="text-ar">Desligar</p>\n				</button>\n			</div>	\n			\n			\n		</div>\n\n		<div class=\'container_2\'>\n			<div class="div-botao_ar_sm">	\n				<button  class=\'botao_ar text-ar\' icon-start (click)="temp17C1()" >\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>18°\n				</button>\n			</div>\n			\n			<div class="div-botao_ar_sm">\n				<button class=\'botao_ar text-ar\' icon-start (click)="temp18C1()">\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>19°\n				</button>\n			</div>	\n\n			<div class="div-botao_ar_sm">\n				<button class=\'botao_ar text-ar\' icon-start (click)="temp19C1()">\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>20°\n				</button>\n			</div>			\n\n			<div class="div-botao_ar_sm">\n				<button class=\'botao_ar text-ar\' icon-start (click)="temp20C1()">\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>21°\n				</button>\n			</div>			\n		</div>		\n\n\n		<div class="titulo2">Central de Ar 2</div>\n		<div class=\'container_1\'>\n			<div class="div-botao_ar_big">	\n				<button  class=\'botao_ar\' icon-start (click)="ligarC2()">\n				<ion-icon name="snow" class=\'icon_size\'></ion-icon><p class="text-ar">Ligar</p>\n				</button>\n			</div>\n			\n			<div class="div-botao_ar_big">\n				<button class=\'botao_ar\' icon-start (click)="desligarC2()">\n				<ion-icon name="snow" class=\'icon_size\'></ion-icon><p class="text-ar">Desligar</p>\n				</button>\n			</div>	\n			\n			\n		</div>\n\n		<div class=\'container_2\'>\n			<div class="div-botao_ar_sm">	\n				<button  class=\'botao_ar text-ar\' icon-start (click)="temp17C2()" >\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>18°\n				</button>\n			</div>\n			\n			<div class="div-botao_ar_sm">\n				<button class=\'botao_ar text-ar\' icon-start (click)="temp18C2()">\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>19°\n				</button>\n			</div>	\n\n			<div class="div-botao_ar_sm">\n				<button class=\'botao_ar text-ar\' icon-start (click)="temp19C2()">\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>20°\n				</button>\n			</div>			\n\n			<div class="div-botao_ar_sm">\n				<button class=\'botao_ar text-ar\' icon-start (click)="temp20C2()">\n				<ion-icon name="thermometer" class=\'icon_size_sm\'></ion-icon>21°\n				</button>\n			</div>			\n		</div>\n\n		<div class="titulo2">Data Show</div>\n			<div class=\'container_3\'>\n				<div class="div-botao_ds">	\n					<button  class=\'botao_ds text-ds\' icon-start (click)="ligarDS()">\n					<ion-icon name="desktop" class=\'icon_size_ds\'></ion-icon>Ligar / Desligar / Confirmar				</button>\n				</div>\n			</div>\n\n\n		\n		\n\n\n	\n\n</ion-content>\n'/*ion-inline-end:"C:\Users\mathe\Google Drive\TCC2\AppTCC\App2_v01\App2\src\pages\control\control.html"*/,
        }),
        __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["k" /* NavController */], __WEBPACK_IMPORTED_MODULE_1_ionic_angular__["m" /* NavParams */], __WEBPACK_IMPORTED_MODULE_2__ionic_native_bluetooth_serial__["a" /* BluetoothSerial */]])
    ], ControlPage);
    return ControlPage;
}());

//# sourceMappingURL=control.js.map

/***/ })

});
//# sourceMappingURL=1.js.map