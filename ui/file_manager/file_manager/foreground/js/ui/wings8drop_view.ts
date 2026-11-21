// @ts-nocheck
// Copyright 2020 Wings8OS Authors. All rights reserved.
// Author: yudong

import {loadTimeData} from 'chrome://resources/ash/common/load_time_data.m.js';

export class Wings8DropView {
  /**
  * @param {!HTMLElement} element
  */
  constructor(element) {
    /**
     * @private {!HTMLElement}
     */
    this.wings8DropView_ = element;

    /** @private {?HTMLElement} */
    this.comingSoonEl_ = this.wings8DropView_.querySelector('#wings8drop-coming-soon');

    /** @private {?HTMLElement} */
    this.webview_ = this.wings8DropView_.getElementsByTagName('webview')[0] || null;

    // Download permission is denied by default in a webview
    // @ts-ignore TS7006: Parameter 'element' implicitly has an 'any' type.
    this.wings8DropView_.addEventListener('permissionrequest', function(e) {
      if (e.permission === 'download') {
        e.request.allow();
      }
    });

    this.loaded_ = false;
    this.setUrl();
  }

  setUrl() {
    if (this.isComingSoonEnabled_()) {
      return;
    }

    const webview = this.webview_;
    if (webview && !webview.src) {
      this.wings8DropView_.addEventListener(
        "contentload",
        this.onContentLoad_.bind(this),
      );
      webview.src = loadTimeData.getString("WINGS8_DROP_URL");
    }
  }

  /** @private */
  isComingSoonEnabled_() {
    // Flag to swap between the placeholder and the real Wings8Drop webview.
    return loadTimeData.getBoolean('WINGS8DROP_COMING_SOON_ENABLED');
  }

  show() {
    const comingSoonEnabled = this.isComingSoonEnabled_();

    if (this.comingSoonEl_) {
      this.comingSoonEl_.hidden = !comingSoonEnabled;
    }

    if (this.webview_) {
      this.webview_.hidden = comingSoonEnabled;
    }

    if (!comingSoonEnabled) {
      if (!this.loaded_) {
        this.hideSpinnerCallback_ =
          window.fileManager.spinnerController.showWithDelay(
            100,
            this.onSpinnerShow_.bind(this),
          );
      }
      this.setUrl();
    } else {
      // No remote content to load => ensure spinner doesn't stick around.
      this.hideSpinner_();
    }

    this.wings8DropView_.hidden = false;
  }

  hide() {
    this.wings8DropView_.hidden = true;
    this.hideSpinner_();
  }

  onContentLoad_() {
    this.loaded_ = true;
    this.hideSpinner_();
  }

  onSpinnerShow_() {}

  hideSpinner_() {
    if (this.hideSpinnerCallback_) {
      this.hideSpinnerCallback_();
      this.hideSpinnerCallback_ = null;
    }
  }
}
