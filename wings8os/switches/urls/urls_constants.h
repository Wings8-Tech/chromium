// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_URLS_CONSTANTS_
#define CHROMEOS_WINGS8OS_SWITCHES_URLS_CONSTANTS_

#include <string>
#include "chromeos/chromeos_export.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os::constants {

CHROMEOS_EXPORT extern const char kDefaultTestUrl[];
CHROMEOS_EXPORT extern const char kWings8OSHomePageUrl[];
CHROMEOS_EXPORT extern const char kOpenWings8HomePageUrl[];

CHROMEOS_EXPORT extern const char kWings8OSStoreBaseUrl[];
CHROMEOS_EXPORT extern const char kWings8OSAccountBaseUrl[];

extern const char kWings8OSForumURL[];
extern const char kWings8OSRemoteDesktopURL[];
extern const char kWings8OSNotesAppURL[];
extern const char kWings8OSHelpURL[];
extern const char kWings8OSReleaseNotesURL[];
extern const char kWings8OSNewsURL[];
extern const char kMultiDeviceLearnMoreURL[];
extern const char kLanguageSettingsLearnMoreUrl[];
extern const char kLinuxAppsLearnMoreURL[];
extern const char kOnlineEulaURLPath[];
extern const char kOnlinePrivacyURLPath[];
extern const char kEulaURLPath[];
extern const char kPrivacyURLPath[];
extern const char kWings8AccessibilityHelpURL[];
extern const char kWings8NewGestureHelpURL[];
extern const char kSmbSharesLearnMoreURL[];
extern const char kCupsPrintLearnMoreURL[];
extern const char kNaturalScrollHelpURL[];
extern const char kControlledScrollingHelpURL[];
extern const char kTimeZoneSettingsLearnMoreURL[];
extern const char kResetProfileSettingsLearnMoreURL[];
extern const char kCrosBatterySaverLearnMoreURL[];

CHROMEOS_EXPORT extern const char kWings8OSAccountURL[];
CHROMEOS_EXPORT extern const char kWings8OSAccountChooserURL[];
CHROMEOS_EXPORT extern const char kWings8OSPasswordManagerURL[];

CHROMEOS_EXPORT extern const char kGoogleDriveBuyStorageUrl[];
CHROMEOS_EXPORT extern const char kGoogleDriveOverviewUrl[];
CHROMEOS_EXPORT extern const char kGoogleDriveHelpUrl[];
CHROMEOS_EXPORT extern const char kGoogleDriveOfflineHelpUrl[];
CHROMEOS_EXPORT extern const char kGoogleDriveRootUrl[];
CHROMEOS_EXPORT extern const char kHelpURLFormat[];
CHROMEOS_EXPORT extern const char kHelpURLNoTaskForFile[];
CHROMEOS_EXPORT extern const char kWings8DropUrl[];

CHROMEOS_EXPORT extern const char kWings8ExperimentTpmFallbackUrl[];

extern const char kEolNotificationURL[];
extern const char kKeyboardShortcutHelpPageUrl[];
extern const char kWings8OSEnableWidevineLearnMoreURL[];

extern const char kWifiHiddenNetworkURL[];
extern const char kBluetoothPairingLearnMoreUrl[];
extern const char kFileManagerHelpURL[];
extern const char kTabletModeGesturesLearnMoreURL[];
extern const char kRuntimeHostPermissionsHelpURL[];
extern const char kFingerprintLearnMoreURL[];

extern const char kWings8OSBackupRestoreLearnMoreURL[];

extern const char kWings8OSToggleArcMediaAutoScanLearnMoreURL[];

extern const char kWings8OSDevModeTransitionLearnMoreURL[];

#if BUILDFLAG(WINGS8OS_DEVICE)
extern const char kWings8OSProductWarrantyDefaultURL[];
#endif

#if !BUILDFLAG(USE_WINGS8OS_COM)
extern const char kWings8OSDiscordServerURL[];
extern const char kWings8OSTelegramGroupURL[];
#endif
}  // namespace wings8os::constants

#endif
