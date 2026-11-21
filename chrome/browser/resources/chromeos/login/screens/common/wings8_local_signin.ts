// Copyright 2025 wings8 technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/**
 * @fileoverview Polymer element for displaying material design wings8 local signin
 */

import { PolymerElementProperties } from '//resources/polymer/v3_0/polymer/interfaces.js';
import { PolymerElement } from '//resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import { LoginScreenMixin } from '../../components/mixins/login_screen_mixin.js';
import { OobeI18nMixin } from '../../components/mixins/oobe_i18n_mixin.js';
import { OobeDialogHostMixin } from '../../components/mixins/oobe_dialog_host_mixin.js';
import { MultiStepMixin } from '../../components/mixins/multi_step_mixin.js';

import { OobeUiState } from '../../components/display_manager_types.js';

import { CrInputElement } from '//resources/ash/common/cr_elements/cr_input/cr_input.js';
import { assert } from '//resources/js/assert.js';

import '//resources/ash/common/cr_elements/icons.html.js';
import '//resources/polymer/v3_0/paper-progress/paper-progress.js';
import '//resources/polymer/v3_0/iron-icon/iron-icon.js';
import '../../components/oobe_icons.html.js';
import '../../components/buttons/oobe_back_button.js';
import '../../components/buttons/oobe_next_button.js';
import '../../components/buttons/oobe_text_button.js';
import '../../components/common_styles/oobe_common_styles.css.js';
import '../../components/common_styles/oobe_dialog_host_styles.css.js';
import '../../components/dialogs/oobe_adaptive_dialog.js';

import { getTemplate } from './wings8_local_signin.html.js';

enum WINGS8_LOCAL_SIGNIN_ERROR_STATE {
  NONE = 0,
  BAD_USERNAME = 1,
  BAD_AUTH_PASSWORD = 2,
  BAD_CONFIRM_PASSWORD = 3,
  BAD_USERNAME_OR_PASSWORD_ERROR = 4,
  BAD_AUTH_PASSWORD_TOO_SHORT = 5,
};

enum Wings8LocalSigninUIState {
  SIGNUP = 'signup',
  SIGNIN = 'signin',
};

interface Wings8LocalSigninData {
  emailDomain: string;
  showUsersOnSignin: boolean;
}

const Wings8LocalSigninBase = OobeDialogHostMixin(LoginScreenMixin(MultiStepMixin(OobeI18nMixin(PolymerElement))));

export class Wings8LocalSignin extends Wings8LocalSigninBase {
  static get is() {
    return 'wings8-local-signin-element' as const;
  }

  static get template() {
    return getTemplate();
  }

  static get properties(): PolymerElementProperties {
    return {
      loading: { type: Boolean, value: false },
      /**
       * Whether the device is currently online.
       * Used to hide "Create a new local account" entry point when internet is available.
       */
      isOnline_: { type: Boolean, value: true },
      userRealm: { type: String, value: '' },
      userName: { type: String, value: '', observer: 'userNameObserver_' },
      errorState: {
        type: Number,
        value: WINGS8_LOCAL_SIGNIN_ERROR_STATE.NONE,
        observer: 'errorStateObserver_',
      },
      showUsersOnSignin_: {
        type: Boolean,
        value: true,
      },
      showSigninButton_: {
        type: Boolean,
        value: false,
        computed: 'computeShowSigninButton_(showUsersOnSignin_, uiStep)',
      },
      userInvalid:
        { type: Boolean, value: false, observer: 'userInvalidObserver_' },
      authPasswordInvalid:
        { type: Boolean, value: false, observer: 'authPasswordInvalidObserver_' },
      authPasswordConfirmInvalid:
        { type: Boolean, value: false, observer: 'authPasswordConfirmInvalidObserver_' },
      authSigninPasswordInvalid:
        { type: Boolean, value: false, observer: 'authSigninPasswordInvalidObserver_' },
    };
  }

  private loading: boolean;
  private isOnline_: boolean;
  private errorStateLocked_: boolean;
  private userName: string;
  private userRealm: string;
  private errorState: WINGS8_LOCAL_SIGNIN_ERROR_STATE;
  private userInvalid: boolean;
  private authPasswordInvalid: boolean;
  private authPasswordConfirmInvalid: boolean;
  private passwordInput: CrInputElement;
  private passwordConfirmInput: CrInputElement;
  private signinPasswordInput: CrInputElement;
  private userInput: CrInputElement;
  private showUsersOnSignin_: boolean;
  private showSigninButton_: boolean;
  private authSigninPasswordInvalid: boolean;
  private hadAlternateRetry_: boolean;

  constructor() {
    super();
    this.errorStateLocked_ = false;
    this.hadAlternateRetry_ = false;
  }

  override get EXTERNAL_API(): string[] {
    return ['reset', 'setErrorState'];
  }

  override get UI_STEPS() {
    return Wings8LocalSigninUIState;
  }

  override defaultUIStep() {
    return Wings8LocalSigninUIState.SIGNUP;
  }


  override ready() {
    super.ready();
    this.initializeLoginScreen('Wings8LocalSigninScreen');

    this.setupConnectivityListener_();

    const passwordInput =
      this.shadowRoot?.querySelector<CrInputElement>('#passwordInput');
    assert(passwordInput instanceof CrInputElement);
    this.passwordInput = passwordInput;

    const passwordConfirmInput =
      this.shadowRoot?.querySelector<CrInputElement>('#passwordConfirmInput');
    assert(passwordConfirmInput instanceof CrInputElement);
    this.passwordConfirmInput = passwordConfirmInput;

    const userInput =
      this.shadowRoot?.querySelector<CrInputElement>('#userInput');
    assert(userInput instanceof CrInputElement);
    this.userInput = userInput;

    const signinPasswordInput =
      this.shadowRoot?.querySelector<CrInputElement>('#signinPasswordInput');
    assert(signinPasswordInput instanceof CrInputElement);
    this.signinPasswordInput = signinPasswordInput;
  }

  private setupConnectivityListener_(): void {
    // Use browser-reported connectivity state for UI toggles.
    this.isOnline_ = navigator.onLine;
    window.addEventListener('online', () => {
      this.isOnline_ = true;
    });
    window.addEventListener('offline', () => {
      this.isOnline_ = false;
    });
  }

  override getOobeUIInitialState() {
    return OobeUiState.WINGS8_LOCAL_SIGNIN;
  }

  override onBeforeShow(data: Wings8LocalSigninData) {
    super.onBeforeShow(data);
    if (data && 'emailDomain' in data) {
      this.userRealm = '@' + data['emailDomain'];
    }
    if (data && 'showUsersOnSignin' in data) {
      this.showUsersOnSignin_ = data.showUsersOnSignin;
    }
    this.focus_();
  }

  setErrorState(username: string, errorState: WINGS8_LOCAL_SIGNIN_ERROR_STATE) {
    this.userName = username;
    this.errorState = errorState;
    this.loading = false;
  }

  reset() {
    this.userInput.value = '';
    this.passwordInput.value = '';
    this.passwordConfirmInput.value = '';
    this.errorState = WINGS8_LOCAL_SIGNIN_ERROR_STATE.NONE;
    this.hadAlternateRetry_ = false;
  }

  focus_() {
    if (!this.userInput.value) {
      this.userInput.focus();
    } else {
      this.passwordInput.focus();
    }
  }

  errorStateObserver_() {
    if (this.errorStateLocked_)
      return;

    this.errorStateLocked_ = true;

    this.userInvalid = this.errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_USERNAME;
    this.authPasswordInvalid = this.errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_AUTH_PASSWORD || this.errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_AUTH_PASSWORD_TOO_SHORT;
    this.authPasswordConfirmInvalid = this.errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_CONFIRM_PASSWORD;
    this.authSigninPasswordInvalid = this.errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_USERNAME_OR_PASSWORD_ERROR;

    // // Auto-retry once with alternate encoding for legacy accounts that may have
    // // stored a base64-encoded password during initial creation.
    // if (this.uiStep === Wings8LocalSigninUIState.SIGNIN &&
    //     this.errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_USERNAME_OR_PASSWORD_ERROR &&
    //     !this.hadAlternateRetry_) {
    //   this.hadAlternateRetry_ = true;

    //   // Build username same as onSubmit_()
    //   let user = /** @type {string} */ (this.userInput.value);
    //   if (!user.includes('@') && this.userRealm) {
    //     user += this.userRealm;
    //   }

    //   // Base64-encode the UTF-8 bytes of the entered password.
    //   const enc = new TextEncoder();
    //   const bytes = enc.encode(this.signinPasswordInput.value || '');
    //   let bin = '';
    //   for (let i = 0; i < bytes.length; ++i) bin += String.fromCharCode(bytes[i]);
    //   const altPassword = btoa(bin);

    //   console.warn('[Wings8LocalSignin] BAD_AUTH detected, retrying once with base64-encoded password');
    //   this.loading = true;
    //   chrome.send('completeFtAuthentication', [false, user, altPassword]);
    //   // Keep lock until after we send the retry; UI will update on next result.
    // }

    this.errorStateLocked_ = false;
  }

  onSubmit_() {
    this.userInvalid = /^[a-zA-Z][a-zA-Z0-9\.\-]*$/.test(this.userInput.value) === false;
    if (this.userInvalid)
      return;
    if (this.uiStep === Wings8LocalSigninUIState.SIGNUP) {
      this.authPasswordInvalid = !this.passwordInput.validate();
      if (this.authPasswordInvalid)
        return;
      this.authPasswordConfirmInvalid = !this.passwordConfirmInput.validate() || (this.passwordInput.value !== this.passwordConfirmInput.value);
      if (this.authPasswordConfirmInvalid)
        return;
    } else if (this.uiStep === Wings8LocalSigninUIState.SIGNIN) {
      this.authSigninPasswordInvalid = !this.signinPasswordInput.validate();
      if (this.authSigninPasswordInvalid)
        return;
    } else {
      return;
    }

    var user = /** @type {string} */ (this.userInput.value);
    if (!user.includes('@') && this.userRealm)
      user += this.userRealm;
    let username = user;
    let password = '';
    let newUser = this.uiStep === Wings8LocalSigninUIState.SIGNUP;
    if (newUser) {
      password = this.passwordInput.value;
    } else {
      password = this.signinPasswordInput.value;
    }
    var msg = {
      newUser,
      username,
      password,
    };
    this.loading = true;
    // WINGS8OS: the C++ HandleCompleteAuth callback expects 5 arguments
    // (newUser, username, password, accessToken, refreshToken). Local accounts
    // have no online tokens, so pad with empty strings to satisfy the
    // WebUI::Call arity check (CHECK_EQ) — empty tokens are ignored.
    chrome.send('completeFtAuthentication', [msg.newUser, msg.username, msg.password, '', '']);
  }

  getInvalidPasswordMessage_(locale: string, errorState: WINGS8_LOCAL_SIGNIN_ERROR_STATE) {
    if (errorState === WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_AUTH_PASSWORD_TOO_SHORT) {
      return this.i18nDynamic(locale, 'wings8osLocalSigninInvalidPasswordTooShort');
    }
    return this.i18nDynamic(locale, 'wings8osLocalSigninInvalidPassword');
  }

  onBackButton_() {
    this.userActed('accountTypeSelectionBack');
  }

  onKeydownUserInput_(e: KeyboardEvent) {
    this.errorState = WINGS8_LOCAL_SIGNIN_ERROR_STATE.NONE;
    if (e.key == 'Enter') {
      if (this.uiStep === Wings8LocalSigninUIState.SIGNUP) {
        this.switchTo_(this.passwordInput);
      } else if (this.uiStep === Wings8LocalSigninUIState.SIGNIN) {
        this.switchTo_(this.signinPasswordInput);
      }
    }
  }

  userNameObserver_() {
    if (this.userRealm && this.userName &&
      this.userName.endsWith(this.userRealm)) {
      this.userName = this.userName.replace(this.userRealm, '');
    }
  }

  onKeydownAuthPasswordInput_(e: KeyboardEvent) {
    this.errorState = WINGS8_LOCAL_SIGNIN_ERROR_STATE.NONE;
    if (e.key == 'Enter')
      this.switchTo_(this.passwordConfirmInput) || this.onSubmit_();
  }

  onKeydownAuthPasswordConfirmInput_(e: KeyboardEvent) {
    this.authPasswordConfirmInvalid = false;
    if (e.key == 'Enter')
      this.onSubmit_();
  }

  onKeydownAuthSigninPasswordInput_(e: KeyboardEvent) {
    this.errorState = WINGS8_LOCAL_SIGNIN_ERROR_STATE.NONE;
    if (e.key == 'Enter')
      this.onSubmit_();
  }

  switchTo_(ele: CrInputElement) {
    if (!ele.disabled && ele.value.length == 0) {
      ele.focus();
      return true;
    }
    return false;
  }

  userInvalidObserver_(isInvalid: boolean) {
    this.setErrorState_(isInvalid, WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_USERNAME);
  }

  authPasswordInvalidObserver_(isInvalid: boolean) {
    this.setErrorState_(
      isInvalid, WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_AUTH_PASSWORD);
  }

  authPasswordConfirmInvalidObserver_(isInvalid: boolean) {
    this.setErrorState_(
      isInvalid, WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_CONFIRM_PASSWORD);
  }

  authSigninPasswordInvalidObserver_(isInvalid: boolean) {
    this.setErrorState_(
      isInvalid, WINGS8_LOCAL_SIGNIN_ERROR_STATE.BAD_USERNAME_OR_PASSWORD_ERROR);
  }

  setErrorState_(isInvalid: boolean, error: WINGS8_LOCAL_SIGNIN_ERROR_STATE) {
    if (this.errorStateLocked_)
      return;
    this.errorStateLocked_ = true;

    if (isInvalid)
      this.errorState = error;
    else
      this.errorState = WINGS8_LOCAL_SIGNIN_ERROR_STATE.NONE;

    this.errorStateLocked_ = false;
  }

  onGotoSignupClicked_() {
    this.reset();
    this.loading = false;
    this.setUIStep(Wings8LocalSigninUIState.SIGNUP);
  }

  onGotoSigninClicked_() {
    this.reset();
    this.loading = false;
    this.setUIStep(Wings8LocalSigninUIState.SIGNIN);
  }

  computeShowSigninButton_(showUsersOnSignin: boolean, uiStep: Wings8LocalSigninUIState) {
    return !showUsersOnSignin && uiStep === Wings8LocalSigninUIState.SIGNUP;
  }
}

declare global {
  interface HTMLElementTagNameMap {
    [Wings8LocalSignin.is]: Wings8LocalSignin;
  }
}

customElements.define(Wings8LocalSignin.is, Wings8LocalSignin);
