// Copyright (c) 2021 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_PREF_NAMES_H_
#define CHROMEOS_WINGS8OS_PREF_NAMES_H_

#include "wings8os/build/config/buildflags.h"

namespace wings8os {
namespace prefs {

extern const char
    kPrefHideWings8OSStoreIcon[];  // registered in
                                 // chrome/browser/ui/browser_ui_prefs.cc

extern const char kWings8OSImprovementPlanEnabled[];

// local state
extern const char kCurrentEnableArcIMEGlobally[];
extern const char kEnableArcIMEGlobally[];

extern const char kForceTpmFallbackNecessary[];
extern const char kCurrentForceTpmFallback[];
extern const char kForceTpmFallback[];

extern const char kShowSwitchTabletLaptopButton[];
extern const char kShowRebootButtonInTray[];
extern const char kShowRotateScreenButton[];

extern const char kOfflineAutoSigninAccountIdKey[];
extern const char kOfflineAutoSigninPassword[];
extern const char kOfflineAutoSigninPasswordFormat[];
extern const char kOfflineAutoSigninIsChromeLastSignout[];

extern const char kConnectApiUserId[];
extern const char kWings8OsDeviceUid[];
extern const char kConnectApiUserStatus[];

// Whether the Wings8 online account of this profile has an active subscription
// (Pro/Pro+). Written after a successful /v1/connect/os/subscription check;
// false for local accounts, Freemium accounts, or when the check never ran.
extern const char kWings8SubscriptionActive[];

// True when the fleet admin deactivated ALL Wings8OS download seats of this
// account. Unlike plain Freemium (never punished), this is an explicit
// revocation: the session is closed and sign-in is refused until reactivated.
extern const char kWings8SeatDeactivated[];

// same with kFactoryResetRequested in chrome/common/pref_names.cc
// dep conflict issue
extern const char kFactoryResetRequested[];

extern const char kRebootRequiredForWidevine[];

// Whether CPU Turbo Boost is enabled (Wings8OS Settings toggle, applied
// via /usr/share/wings8os_shell/cpu_turbo.sh). Default true.
extern const char kCpuTurboEnabled[];

extern const char kWings8AssistantEnabled[];
extern const char kWings8AssistantExtraAcceleratorEnabled[];

// Wings8OS auth token lifecycle (OSCrypt-encrypted, persists across restarts).
extern const char kWings8OsAuthAccessTokenEncrypted[];
extern const char kWings8OsAuthRefreshTokenEncrypted[];
extern const char kWings8OsAuthEmail[];
extern const char kWings8OsAuthIssuedAt[];

// Monotonic SaaS password version last seen by this device. When the value
// returned by osLogin/getOsToken/refreshtoken differs, the SaaS password was
// changed and the device must re-seal its cryptohome key (force an online
// sign-in so the standard password-change flow runs).
extern const char kWings8OsAuthPasswordVersion[];

// Per-account map (email -> OSCrypt ciphertext of the last password that
// successfully unlocked the cryptohome). Wings8OS uses it to re-seal the
// cryptohome key automatically after a SaaS password change, so the user is
// never asked for their old password.
extern const char kWings8OsSavedPasswords[];

// Per-account map (email -> OSCrypt ciphertext of a random per-account vault
// secret). For Wings8 ONLINE accounts the cryptohome vault is sealed with this
// secret instead of the SaaS password, so a SaaS password change never requires
// re-sealing the vault: the pod validates the typed password online and unlocks
// with this stable secret.
extern const char kWings8OsVaultSecrets[];

extern const char kWings8OSArcMediaAutoScanEnabled[];

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
extern const char kWings8LicenseShouldShowInSettings[];
extern const char kWings8LicenseStateType[];
extern const char kWings8LicenseEnforcementLevel[];
extern const char kWings8LicenseEnforcementLogOutInterval[];
#endif

#if BUILDFLAG(USE_WINGS8OS_COM)
extern const char kCrostiniInstallerNotificationUserInteracted[];
#endif

}  // namespace prefs
}  // namespace wings8os

#endif
