// Copyright 2020 Wings8OS Authors. All rights reserved.
// Author: yudong

import {Wings8DropView} from './ui/wings8drop_view.js';
import {FileManagerUI} from './ui/file_manager_ui.js';
import {DirectoryModel} from './directory_model.js';

export class Wings8DropViewController {
  private wings8DropView_: Wings8DropView;
  private directoryModel_: DirectoryModel;
  private ui_: FileManagerUI;
  /**
   * @param {!Wings8DropView} wings8DropView Wings8Drop view.
   * @param {!DirectoryModel} directoryModel Directory model.
   */
  constructor(ui: FileManagerUI, wings8DropView: Wings8DropView, directoryModel: DirectoryModel) {
    console.log('Wings8DropViewController constructor');
    this.ui_ = ui;
    /**
     * @private {!Wings8DropView}
     */
    this.wings8DropView_ = wings8DropView;

    /**
     * @private {!DirectoryModel}
     */
    this.directoryModel_ = directoryModel;

    this.directoryModel_.addEventListener(
        'wings8drop-started', this.onWings8DropStarted_.bind(this));
    this.directoryModel_.addEventListener(
        'wings8drop-stopped', this.onWings8DropStopped_.bind(this));
  }

  hideActionButtonsAndTable_() {
    console.log('hideActionButtons_');
    this.ui_.sortButton.setAttribute('hidden', '');
    this.ui_.toggleViewButton.setAttribute('hidden', '');
    this.ui_.listContainer.table.setAttribute('hidden', '');
  }

  showActionButtonsAndTable_() {
    console.log('showActionButtons_');
    this.ui_.sortButton.removeAttribute('hidden');
    this.ui_.toggleViewButton.removeAttribute('hidden');
    this.ui_.listContainer.table.removeAttribute('hidden');
  }

  onWings8DropStarted_() {
    console.log('onWings8DropStarted_');
    this.hideActionButtonsAndTable_();
    this.wings8DropView_.show();
  }

  onWings8DropStopped_() {
    console.log('onWings8DropStopped_');
    this.wings8DropView_.hide();
    this.showActionButtonsAndTable_();
  }
}
