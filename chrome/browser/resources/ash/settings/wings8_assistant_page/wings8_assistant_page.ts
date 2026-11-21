import 'chrome://resources/ash/common/cr_elements/cr_link_row/cr_link_row.js';
import '../controls/settings_toggle_button.js';
import '../os_settings_page/settings_card.js';
import '../settings_shared.css.js';

import {PrefsMixin} from '/shared/settings/prefs/prefs_mixin.js';
import {loadTimeData} from 'chrome://resources/js/load_time_data.js';
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {Section} from '../mojom-webui/routes.mojom-webui.js';
import {isWings8AiHidden} from '../common/load_time_booleans.js';

import {getTemplate} from './wings8_assistant_page.html.js';

const OsSettingsWings8AssistantPageElementBase = PrefsMixin(PolymerElement);

export class OsSettingsWings8AssistantPageElement extends OsSettingsWings8AssistantPageElementBase {
  static get is() {
    return 'os-settings-wings8-assistant-page';
  }

  static get template() {
    return getTemplate();
  }

  static get properties() {
    return {
      section_: {
        type: Number,
        value: Section.kWings8Assistant,
        readOnly: true,
      },

      isWings8AiHidden_: {
        type: Boolean,
        value: () => isWings8AiHidden(),
        readOnly: true,
      },
    };
  }

  // constructor() {
  //   super();
  // }
  //
  // override ready() {
  //   super.ready();
  // }
  //
  // override connectedCallback() {
  //   super.connectedCallback();
  // }
  onSettingsClicked_() {
    let enabled = false;
    try {
       enabled = this.getPref<boolean>('wings8_assistant_enabled').value;
    } catch (e) {
      console.error('Get pref wings8_assistant_enabled error', e);
    }

    if (!enabled) return;
    window.open('chrome://wings8os-ai/settings');
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'os-settings-wings8-assistant-page': OsSettingsWings8AssistantPageElement;
  }
}

customElements.define(OsSettingsWings8AssistantPageElement.is, OsSettingsWings8AssistantPageElement);
