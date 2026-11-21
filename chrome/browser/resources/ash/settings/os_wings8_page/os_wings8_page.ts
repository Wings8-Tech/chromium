// os-settings-wings8-page

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import 'chrome://resources/ash/common/cr_elements/cr_shared_style.css.js';

import {I18nMixin} from 'chrome://resources/ash/common/cr_elements/i18n_mixin.js';
import {Router, routes} from '../router.js';
import {RouteOriginMixin} from '../common/route_origin_mixin.js';
import {Section} from '../mojom-webui/routes.mojom-webui.js';
import {loadTimeData} from 'chrome://resources/js/load_time_data.js';
import '../os_settings_page/settings_card.js';
import '../os_settings_page/os_settings_subpage.js';
import '../settings_shared.css.js';
import './wings8os_account.js';
// import './wings8os_drivers.js';
import './wings8os_remoting.js';
import './wings8os_tweak_ui.js';
import './wings8os_experiment.js';
import './wings8os_more_info.js';
import './wings8os_dev_mode.js';
// <if expr="use_wings8os_license">
import './wings8os_license_info.js';
// </if>

import {getTemplate} from './os_wings8_page.html.js';

const OsSettingsWings8PageElementBase = 
  RouteOriginMixin(I18nMixin(PolymerElement));

/** @polymer */
class OsSettingsWings8PageElement extends OsSettingsWings8PageElementBase {
  static get is() {
    return 'os-wings8-page' as const;
  }

  static get template() {
    return getTemplate();
  }

  static get properties() {
    return {
      section_: {
        type: Number,
        value: Section.kWings8Os,
        readOnly: true,
      },
      isWings8Account_: {
        type: Boolean,
        value() {
          return loadTimeData.getBoolean('isWings8Profile');
        },
      },
      isGuest_: {
        type: Boolean,
        value() {
          return loadTimeData.getBoolean('isGuest');
        },
      },

// <if expr="use_wings8os_license">
      showWings8OsLicense_: {
        type: Boolean,
        value() {
          return loadTimeData.valueExists('showWings8OsLicense') && loadTimeData.getBoolean('showWings8OsLicense');
        },
      },
// </if>

      showToggleRebootButtonInTray: {
        type: Boolean,
        value() {
          // some specified board cannot reboot
          const ret = loadTimeData.getBoolean('showToggleRebootButtonInTray');
          console.log('showToggleRebootButtonInTray', ret);
          return ret;
        },
      },
      showToggleRotateScreenButton: {
        type: Boolean,
        value() {
          // only amd64-wings8os/amd64-generic shouldShowToggleShowRotateScreenButton is true
          return loadTimeData.getBoolean('showToggleRotateScreenButton');
        },
      },
      showToggleSwitchTabletLaptopButton: {
        type: Boolean,
        value() {
          return loadTimeData.getBoolean('showToggleSwitchTabletLaptopButton');
        },
      },

      authFactorHasPassword_: Boolean,

      authFactorHasPasswordOrPin_: Boolean,
    };
  }

  private isWings8Account_: boolean;
  private isGuest_: boolean;
  private showWings8OsLicense_: boolean;
  private showToggleRebootButtonInTray: boolean;
  private showToggleRotateScreenButton: boolean;
  private showToggleSwitchTabletLaptopButton: boolean;
  private authFactorHasPassword_: boolean;
  private authFactorHasPasswordOrPin_: boolean;

  constructor() {
    super();
    this.route = routes.WINGS8OS;
    console.log('os-settings-wings8-page ready');
    // <if expr="_google_chrome">
    console.log('this is a test for build tools')
    // </if>
  }

  override connectedCallback() {
    super.connectedCallback();
    console.log('os-settings-wings8-page attached');
  }

  showWings8OsTweakUi_() {
    return this.showToggleRotateScreenButton || this.showToggleRebootButtonInTray || this.showToggleSwitchTabletLaptopButton;
  }

  onAuthFactorHasPasswordChanged_(e: CustomEvent) {
    this.authFactorHasPassword_ = e.detail;
  }

  onAuthFactorHasPasswordOrPinChanged_(e: CustomEvent) {
    this.authFactorHasPasswordOrPin_ = e.detail;
  }

// <if expr="use_wings8os_license">
  onLicenseInfoClick_() {
    if (!this.showWings8OsLicense_) return;
    Router.getInstance().navigateTo(routes.WINGS8OS_LICENSE_INFO);
  }
// </if>
}

customElements.define(
    OsSettingsWings8PageElement.is, OsSettingsWings8PageElement);
