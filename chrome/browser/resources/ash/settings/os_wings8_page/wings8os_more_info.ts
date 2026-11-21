// os-settings-wings8os-more-info
//
import {PolymerElement, mixinBehaviors} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import 'chrome://resources/ash/common/cr_elements/cr_link_row/cr_link_row.js';

import {AboutPageBrowserProxy, AboutPageBrowserProxyImpl} from '../os_about_page/about_page_browser_proxy.js';

import {getTemplate} from './wings8os_more_info.html.js';

const Wings8SettingsMoreInfoPageElementBase = mixinBehaviors(
  [], PolymerElement);

class Wings8SettingsMoreInfoPageElement extends Wings8SettingsMoreInfoPageElementBase {
  static get is() {
    return 'os-settings-wings8os-more-info';
  }
  static get template() {
    return getTemplate();
  }

  static get properties() {
    return {};
  }

  private aboutBrowserProxy_: AboutPageBrowserProxy;
  private hasInternetConnection_: boolean;

  constructor() {
    super();
    this.aboutBrowserProxy_ = AboutPageBrowserProxyImpl.getInstance();
    console.log('os-settings-wings8-more-info ready');
  }

  override connectedCallback() {
    super.connectedCallback();
    console.log('os-settings-wings8-more-info attached');
    this.aboutBrowserProxy_.pageReady();

    this.aboutBrowserProxy_.checkInternetConnection().then(result => {
      this.hasInternetConnection_ = result;
    });
  }

  onReleaseNotesTap_() {
    this.aboutBrowserProxy_.launchReleaseNotes();
  }

  onHelpClick_() {
    this.aboutBrowserProxy_.openOsHelpPage();
  }
}

customElements.define(
    Wings8SettingsMoreInfoPageElement.is, Wings8SettingsMoreInfoPageElement);
