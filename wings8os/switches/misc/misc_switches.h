// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_MISC_SWITCHES_H_
#define CHROMEOS_WINGS8OS_SWITCHES_MISC_SWITCHES_H_

#include <string>
#include "chromeos/chromeos_export.h"

namespace wings8os {
namespace switches {

CHROMEOS_EXPORT bool IsWings8CustomEnabled();

CHROMEOS_EXPORT bool IsTpmDictionaryAttackLockoutIgnored();

CHROMEOS_EXPORT bool IsNonForYouBoard(const std::string& board);

CHROMEOS_EXPORT bool IsInitDevicePolicyWithoutStateKeysAllowed();

CHROMEOS_EXPORT bool IsUnknownPeripheralBatteryNotificationDisabled();

CHROMEOS_EXPORT bool IsDynamicDefaultWallpaperSupported();

CHROMEOS_EXPORT extern const char kWings8OSServiceHostSuffixForTesting[];

CHROMEOS_EXPORT int64_t GetWings8OSAutoSigninDelay();

CHROMEOS_EXPORT bool IsOsInstallButtonHidden();

// Returns true when the Google account login button should be hidden in the
// OOBE / welcome flow (account type selection).
CHROMEOS_EXPORT bool IsGoogleLoginButtonHidden();

CHROMEOS_EXPORT bool IsWings8AiHidden();

} // switches
} // wings8os

#endif
