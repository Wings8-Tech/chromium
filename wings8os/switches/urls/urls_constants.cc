// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/urls/urls_constants.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os::constants {

#if BUILDFLAG(USE_WINGS8OS_COM)

const char kDefaultTestUrl[] = "http://wings8tech.com/204";
const char kWings8OSHomePageUrl[] = "https://wings8.org";
const char kOpenWings8HomePageUrl[] = "https://wings8.org";

const char kWings8OSStoreBaseUrl[] = "https://chromewebstore.google.com/category/extensions";
const char kWings8OSAccountBaseUrl[] = "https://86db242e-958e-432e-a6c2-0b19a92beeb6.auth-app.wings8tech.com";

const char kWings8OSForumURL[] = "https://wings8.org/";
const char kWings8OSRemoteDesktopURL[] = "https://rdp.wings8.org/";
const char kWings8OSNotesAppURL[] = "https://wings8.org"; // https://notes.wings8.org
const char kWings8OSHelpURL[] = "https://wings8.org/?ospath=help/";
const char kWings8OSReleaseNotesURL[] = "https://wings8.org/?ospath=release";
const char kWings8OSNewsURL[] = "https://wings8.org/?ospath=blog";
const char kMultiDeviceLearnMoreURL[] = "https://wings8.org/?ospath=docs";
const char kLanguageSettingsLearnMoreUrl[] = "https://wings8.org/?ospath=docs/manual/customize-settings/language/manage-your-wings8os-devices-languages/";
const char kLinuxAppsLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/add-apps-and-extensions/set-up-linux-on-your-wings8os-device/";
const char kOnlineEulaURLPath[] = "https://www.wings8.org/conditions-utilisation/?agent=oobe";
const char kOnlinePrivacyURLPath[] = "https://www.wings8.org/politique-confidentialite/?agent=oobe";
const char kEulaURLPath[] = "https://www.wings8.org/conditions-utilisation";
const char kPrivacyURLPath[] = "https://www.wings8.org/politique-confidentialite";
const char kWings8AccessibilityHelpURL[] = "https://wings8.org/?ospath=docs/manual/explore-accessibility";
const char kWings8NewGestureHelpURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/use-tablets/use-gestures-or-buttons-to-navigate-in-tablet-mode";
const char kSmbSharesLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/manage-your-apps/files-and-downloads/add-network-file-share-system/";
const char kCupsPrintLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/connect-your-wings8os-device/connect-to-other-devices/set-up-your-printer";
const char kNaturalScrollHelpURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/appearance/use-your-wings8os-device-touchpad/";
const char kControlledScrollingHelpURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/appearance/use-your-wings8os-device-touchpad/";
const char kTimeZoneSettingsLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/customize-settings/appearance/set-the-date-and-time/";
const char kResetProfileSettingsLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/customize-settings/privacy/reset-chromium-settings-to-default/";
const char kCrosBatterySaverLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/customize-settings/advanced-settings/battery-saver/";
const char kWings8OSAccountURL[] = "https://account.wings8.org";
const char kWings8OSAccountChooserURL[] = "https://account.wings8.org";
const char kWings8OSPasswordManagerURL[] = "https://account.wings8.org";

const char kGoogleDriveBuyStorageUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveOverviewUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveHelpUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveOfflineHelpUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveRootUrl[] = "https://wings8.org";
const char kHelpURLFormat[] = "https://wings8.org/docs/?ospath=knowledge-base/answer/%d";
const char kHelpURLNoTaskForFile[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/files-and-downloads/file-types-and-external-devices-that-work-on-wings8os-device/";
const char kWings8DropUrl[] = "https://drop.wings8.org";

const char kWings8ExperimentTpmFallbackUrl[] = "https://wings8.org/?ospath=faq/experimental-tpm-fallback";
const char kEolNotificationURL[] = "https://wings8.org/?ospath=eol";
const char kKeyboardShortcutHelpPageUrl[] = "https://wings8.org/?ospath=docs/knowledge-base/recipes/keyboard-shortcuts";
const char kWings8OSEnableWidevineLearnMoreURL[] = "https://wings8.org/?ospath=docs/knowledge-base/recipes/widevine";
const char kWifiHiddenNetworkURL[] = "https://wings8.org/?ospath=docs/manual/connect-your-wings8os-device/connect-to-wi-fi-&-other-networks/manage-wifi-networks/";
const char kBluetoothPairingLearnMoreUrl[] = "https://wings8.org/?ospath=docs/manual/connect-your-wings8os-device/connect-to-other-devices/connect-to-bluetooth-devices/";
const char kFileManagerHelpURL[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/files-and-downloads/open-save-or-delete-files/";
const char kTabletModeGesturesLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/use-tablets/use-gestures-or-buttons-to-navigate-in-tablet-mode";
const char kRuntimeHostPermissionsHelpURL[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/add-apps-and-extensions/add-apps-and-extensions/";
const char kFingerprintLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/users-and-sync/set-up-and-sign-in-with-fingerprint-on-your-wings8os-device";

const char kWings8OSBackupRestoreLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/wings8os-settings/misc#backup-and-restore";

const char kWings8OSToggleArcMediaAutoScanLearnMoreURL[] = "https://wings8.org/?ospath=faq/disable-media-files-scan/";
const char kWings8OSDevModeTransitionLearnMoreURL[] = "https://wings8.org/?ospath=docs/knowledge-base/getting-started/developer-mode";

#if BUILDFLAG(WINGS8OS_DEVICE)
const char kWings8OSProductWarrantyDefaultURL[] = "https://wings8.org";
#endif

#else

const char kDefaultTestUrl[] = "http://chromewebstore.google.com/204";
const char kWings8OSHomePageUrl[] = "https://wings8.org";
const char kOpenWings8HomePageUrl[] = "https://wings8.org/"; // https://wings8.org/openwings8/

// Base URL used to open the extensions store UI.
// NOTE: Keep this without a trailing slash because callers append their own
// paths/query params.
const char kWings8OSStoreBaseUrl[] = "https://chromewebstore.google.com";
const char kWings8OSAccountBaseUrl[] = "https://86db242e-958e-432e-a6c2-0b19a92beeb6.auth-app.wings8tech.com";

const char kWings8OSForumURL[] = "https://wings8.org/"; // https://community.wings8.org/
const char kWings8OSRemoteDesktopURL[] = "https://rdp.wings8.org/";
const char kWings8OSNotesAppURL[] = "https://wings8.org"; // https://notes.wings8.org
const char kWings8OSHelpURL[] = "https://wings8.org/?ospath=help/";
const char kWings8OSReleaseNotesURL[] = "https://wings8.org/?ospath=release";
const char kWings8OSNewsURL[] = "https://wings8.org/?ospath=blog";
const char kMultiDeviceLearnMoreURL[] = "https://wings8.org/?ospath=docs";
const char kLanguageSettingsLearnMoreUrl[] = "https://wings8.org/?ospath=docs/manual/customize-settings/language/manage-your-wings8os-devices-languages/";
const char kLinuxAppsLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/add-apps-and-extensions/set-up-linux-on-your-wings8os-device/";
const char kOnlineEulaURLPath[] = "https://www.wings8.org/conditions-utilisation/?agent=oobe";
const char kOnlinePrivacyURLPath[] = "https://www.wings8.org/politique-confidentialite/?agent=oobe";
const char kEulaURLPath[] = "https://www.wings8.org/conditions-utilisation";
const char kPrivacyURLPath[] = "https://www.wings8.org/politique-confidentialite";
const char kWings8AccessibilityHelpURL[] = "https://wings8.org/?ospath=docs/manual/explore-accessibility";
const char kWings8NewGestureHelpURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/use-tablets/use-gestures-or-buttons-to-navigate-in-tablet-mode";
const char kSmbSharesLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/manage-your-apps/files-and-downloads/add-network-file-share-system/";
const char kCupsPrintLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/connect-your-wings8os-device/connect-to-other-devices/set-up-your-printer";
const char kNaturalScrollHelpURL[] = "https://wings8.org/?ospath=ocs/manual/customize-settings/appearance/use-your-wings8os-device-touchpad/";
const char kControlledScrollingHelpURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/appearance/use-your-wings8os-device-touchpad/";
const char kTimeZoneSettingsLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/customize-settings/appearance/set-the-date-and-time/";
const char kResetProfileSettingsLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/customize-settings/privacy/reset-chromium-settings-to-default/";
const char kCrosBatterySaverLearnMoreURL[] = "https://wings8.org/?ospath=help/manual/customize-settings/advanced-settings/battery-saver/";
const char kWings8OSAccountURL[] = "https://86db242e-958e-432e-a6c2-0b19a92beeb6.auth-app.wings8tech.com";
const char kWings8OSAccountChooserURL[] = "https://86db242e-958e-432e-a6c2-0b19a92beeb6.auth-app.wings8tech.com";
const char kWings8OSPasswordManagerURL[] = "https://86db242e-958e-432e-a6c2-0b19a92beeb6.auth-app.wings8tech.com";

const char kGoogleDriveBuyStorageUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveOverviewUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveHelpUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveOfflineHelpUrl[] = "https://wings8.org/?ospath=docs/knowledge-base";
const char kGoogleDriveRootUrl[] = "https://wings8.org";
const char kHelpURLFormat[] = "https://wings8.org/?ospath=docs/knowledge-base/answer/%d";
const char kHelpURLNoTaskForFile[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/files-and-downloads/file-types-and-external-devices-that-work-on-wings8os-device/";
const char kWings8DropUrl[] = "https://drop.wings8.org";

const char kWings8ExperimentTpmFallbackUrl[] = "https://wings8.org/?ospath=faq/experimental-tpm-fallback";
const char kEolNotificationURL[] = "https://wings8.org/?ospath=eol";
const char kKeyboardShortcutHelpPageUrl[] = "https://wings8.org/?ospath=docs/knowledge-base/recipes/keyboard-shortcuts";
const char kWings8OSEnableWidevineLearnMoreURL[] = "https://wings8.org/?ospath=docs/knowledge-base/recipes/widevine";
const char kWifiHiddenNetworkURL[] = "https://wings8.org/?ospath=docs/manual/connect-your-wings8os-device/connect-to-wi-fi-&-other-networks/manage-wifi-networks/";
const char kBluetoothPairingLearnMoreUrl[] = "https://wings8.org/?ospath=docs/manual/connect-your-wings8os-device/connect-to-other-devices/connect-to-bluetooth-devices/";
const char kFileManagerHelpURL[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/files-and-downloads/open-save-or-delete-files/";
const char kTabletModeGesturesLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/use-tablets/use-gestures-or-buttons-to-navigate-in-tablet-mode";
const char kRuntimeHostPermissionsHelpURL[] = "https://wings8.org/?ospath=docs/manual/manage-your-apps/add-apps-and-extensions/add-apps-and-extensions/";
const char kFingerprintLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/users-and-sync/set-up-and-sign-in-with-fingerprint-on-your-wings8os-device";

const char kWings8OSBackupRestoreLearnMoreURL[] = "https://wings8.org/?ospath=docs/manual/customize-settings/wings8os-settings/misc#backup-and-restore";

const char kWings8OSToggleArcMediaAutoScanLearnMoreURL[] = "https://wings8.org/?ospath=faq/disable-media-files-scan/";

const char kWings8OSDevModeTransitionLearnMoreURL[] = "https://wings8.org/?ospath=docs/knowledge-base/getting-started/developer-mode";

const char kWings8OSDiscordServerURL[] = "https://discord.wings8.org";
const char kWings8OSTelegramGroupURL[] = "https://telegram.wings8.org";
// const char kWings8OSTelegramGroupURL[] = "https://t.me/hi_wings8os";

#if BUILDFLAG(WINGS8OS_DEVICE)
const char kWings8OSProductWarrantyDefaultURL[] = "https://wings8.org"; // https://warrenty.wings8.org
#endif

#endif

}  // wings8os::constants
 