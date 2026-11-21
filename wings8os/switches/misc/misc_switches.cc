// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/misc/misc_switches.h"
#include "base/command_line.h"
#include "base/strings/string_util.h"

namespace wings8os {
namespace switches {

namespace {

const char kWings8DisableCustom[] = "wings8-disable-custom";

const char kEnableTpmDictionaryAttackLockout[] = "wings8os-enable-tpm-da-lockout";

const char kDisallowInitDevicePolicyWithoutStateKeys[] = "disallow-init-device-policy-without-state-keys";

const char kDisableUnknownPeripheralBatteryNotification[] = "disable-unknown-peripheral-battery-notification";

const char kWings8EnableDynamicDefaultWallpaper[] =
  "wings8-dynamic-default-wallpaper";

const char kWings8HideOsInstallButton[] = "wings8-hide-os-install-button";

const char kWings8HideGoogleLoginButton[] = "wings8-hide-google-login-button";

const char kWings8HideWings8Ai[] = "wings8-hide-wings8-ai";

const std::vector<std::string> kNonForYouBoards = {
  "amd64-wings8os",
  "amd64-openwings8",
  "amd64-vmware",
  "amd64-generic",
  "wings8tab_duo-wings8os",
};

const char kWings8AutoSigninDelay[] = "wings8-auto-signin-delay";

}

const char kWings8OSServiceHostSuffixForTesting[] =
  "wings8os-service-host-suffix-for-testing";

bool IsWings8CustomEnabled() {
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(kWings8DisableCustom);
}

bool IsTpmDictionaryAttackLockoutIgnored() {
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(kEnableTpmDictionaryAttackLockout);
}

bool IsNonForYouBoard(const std::string& board) {
  for (const auto& non_for_you_board : kNonForYouBoards) {
    if (non_for_you_board == board) {
      return true;
    }
    if (base::StartsWith(board, non_for_you_board)) {
      return true;
    }
  }
  return false;
}

bool IsInitDevicePolicyWithoutStateKeysAllowed() {
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(kDisallowInitDevicePolicyWithoutStateKeys);
}

bool IsUnknownPeripheralBatteryNotificationDisabled() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kDisableUnknownPeripheralBatteryNotification);
}

bool IsDynamicDefaultWallpaperSupported() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
      kWings8EnableDynamicDefaultWallpaper);
}

int64_t GetWings8OSAutoSigninDelay() {
	std::string delayStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kWings8AutoSigninDelay);
	if (delayStr.empty())
		return 0;
	return (int64_t) std::stoi(delayStr);
}

bool IsOsInstallButtonHidden() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kWings8HideOsInstallButton);
}

bool IsGoogleLoginButtonHidden() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
      kWings8HideGoogleLoginButton);
}

bool IsWings8AiHidden() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kWings8HideWings8Ai);
}

} // switches
} // wings8os
