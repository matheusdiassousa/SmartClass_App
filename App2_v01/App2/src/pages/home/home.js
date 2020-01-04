var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { SuperTabs } from 'ionic2-super-tabs';
import { AlertController } from 'ionic-angular/components/alert/alert-controller';
var HomePage = /** @class */ (function () {
    function HomePage(navCtrl, navParams, alertCtrl) {
        this.navCtrl = navCtrl;
        this.navParams = navParams;
        this.alertCtrl = alertCtrl;
        this.pages = [
            { pageName: 'NewsPage', title: 'News', icon: 'flame', id: 'newsTab' },
            { pageName: 'AboutPage', title: 'About', icon: 'help-circle', id: 'aboutTab' },
            { pageName: 'AccountPage', title: 'Body', icon: 'body', id: 'accountTab' }
        ];
        this.selectedTab = 0;
    }
    HomePage.prototype.onTabSelect = function (ev) {
        var _this = this;
        if (ev.index === 2) {
            var alert_1 = this.alertCtrl.create({
                title: 'Secret Page',
                message: 'Are you sure you want to access that page?',
                buttons: [
                    {
                        text: 'No',
                        handler: function () {
                            _this.superTabs.slideTo(_this.selectedTab);
                        }
                    }, {
                        text: 'Yes',
                        handler: function () {
                            _this.selectedTab = ev.index;
                        }
                    }
                ]
            });
            alert_1.present();
        }
        else {
            this.selectedTab = ev.index;
            this.superTabs.clearBadge(this.pages[ev.index].id);
        }
    };
    __decorate([
        ViewChild(SuperTabs),
        __metadata("design:type", SuperTabs)
    ], HomePage.prototype, "superTabs", void 0);
    HomePage = __decorate([
        IonicPage(),
        Component({
            selector: 'page-home',
            templateUrl: 'home.html',
        }),
        __metadata("design:paramtypes", [NavController, NavParams, AlertController])
    ], HomePage);
    return HomePage;
}());
export { HomePage };
//# sourceMappingURL=home.js.map