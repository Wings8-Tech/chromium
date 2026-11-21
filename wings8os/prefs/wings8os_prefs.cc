// Copyright (c) 2021 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/prefs/wings8os_prefs.h"

#include "base/base64.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "base/values.h"
#include "components/os_crypt/sync/os_crypt.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/scoped_user_pref_update.h"
#include "wings8os/constants/wings8os_constants.h"

namespace wings8os {
namespace prefs {

void RegisterProfilePrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(kWings8OSImprovementPlanEnabled, false);

  registry->RegisterBooleanPref(kWings8AssistantEnabled, false);
  registry->RegisterBooleanPref(kWings8AssistantExtraAcceleratorEnabled, false);

  registry->RegisterBooleanPref(kWings8OSArcMediaAutoScanEnabled, true);

  // Set to true once the Wings8 online account of this profile proves an
  // active Pro/Pro+ subscription via the Connect API. Stays false for local
  // accounts and Freemium accounts.
  registry->RegisterBooleanPref(kWings8SubscriptionActive, false);
  registry->RegisterBooleanPref(kWings8SeatDeactivated, false);
#if BUILDFLAG(USE_WINGS8OS_COM)
  registry->RegisterBooleanPref(kCrostiniInstallerNotificationUserInteracted,
                                false);
#endif
}

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(kForceTpmFallbackNecessary, true);
  registry->RegisterBooleanPref(kCurrentForceTpmFallback, false);
  registry->RegisterBooleanPref(kForceTpmFallback, false);

  registry->RegisterBooleanPref(kEnableArcIMEGlobally, false);
  registry->RegisterBooleanPref(kCurrentEnableArcIMEGlobally, false);

  registry->RegisterStringPref(kOfflineAutoSigninAccountIdKey, std::string());
  registry->RegisterStringPref(kOfflineAutoSigninPassword, std::string());
  registry->RegisterStringPref(kOfflineAutoSigninPasswordFormat, std::string());
  registry->RegisterBooleanPref(kOfflineAutoSigninIsChromeLastSignout, false);

  registry->RegisterStringPref(kConnectApiUserId, std::string());
  registry->RegisterStringPref(kWings8OsDeviceUid, std::string());
  registry->RegisterStringPref(kConnectApiUserStatus, std::string());

  registry->RegisterStringPref(kWings8OsAuthAccessTokenEncrypted, std::string());
  registry->RegisterStringPref(kWings8OsAuthRefreshTokenEncrypted, std::string());
  registry->RegisterStringPref(kWings8OsAuthEmail, std::string());
  registry->RegisterInt64Pref(kWings8OsAuthIssuedAt, 0);
  registry->RegisterInt64Pref(kWings8OsAuthPasswordVersion, 0);
  registry->RegisterDictionaryPref(kWings8OsSavedPasswords);
  registry->RegisterDictionaryPref(kWings8OsVaultSecrets);

  registry->RegisterBooleanPref(kRebootRequiredForWidevine, false);
  registry->RegisterBooleanPref(kCpuTurboEnabled, true);

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
  registry->RegisterBooleanPref(kWings8LicenseShouldShowInSettings, false);
  registry->RegisterIntegerPref(
      kWings8LicenseStateType,
      static_cast<int>(wings8os::constants::LicenseStateType::kUnspecified));
  // kWings8LicenseEnforcementLevel / kWings8LicenseEnforcementLogOutInterval are
  // deliberately NOT registered any more: enforcement state lives in memory
  // in LicenseManager (per profile), so one profile's expired license cannot
  // punish the other profiles through device-wide local_state.
#endif
}

void KeepCurrentPrefs(PrefService* local_state) {
  // prefix with `kCurrent` prefs set here, and read only in other situation
  bool tpm_fallback = local_state->GetBoolean(wings8os::prefs::kForceTpmFallback);
  local_state->SetBoolean(kCurrentForceTpmFallback, tpm_fallback);

  bool enable_arc_ime_globally =
      local_state->GetBoolean(wings8os::prefs::kEnableArcIMEGlobally);
  local_state->SetBoolean(kCurrentEnableArcIMEGlobally,
                          enable_arc_ime_globally);
}

void SetNotNecessaryForceTpmFallback(PrefService* local_state) {
  local_state->SetBoolean(kForceTpmFallbackNecessary, false);
  local_state->SetBoolean(kCurrentForceTpmFallback, false);
  local_state->SetBoolean(kForceTpmFallback, false);
}

void ClearRebootMarkPrefs(PrefService* local_state) {
  local_state->SetBoolean(kRebootRequiredForWidevine, false);
}

void ClearOneShotProfilePrefs(PrefService* prefs) {
  prefs->ClearPref(kWings8OSArcMediaAutoScanEnabled);
}

void SaveWings8AccountPassword(PrefService* local_state,
                             const std::string& email,
                             const std::string& password) {
  if (!local_state || email.empty() || password.empty()) {
    return;
  }
  std::string encrypted;
  if (!OSCrypt::EncryptString(password, &encrypted)) {
    LOG(ERROR) << "[WINGS8OS] Failed to encrypt saved password";
    return;
  }
  const std::string key = base::ToLowerASCII(email);
  ScopedDictPrefUpdate update(local_state, kWings8OsSavedPasswords);
  update->Set(key, base::Base64Encode(encrypted));
  VLOG(1) << "[WINGS8OS] Saved device password for " << key;
}

std::string GetWings8AccountPassword(PrefService* local_state,
                                   const std::string& email) {
  if (!local_state || email.empty()) {
    return std::string();
  }
  const base::Value::Dict& dict = local_state->GetDict(kWings8OsSavedPasswords);
  const std::string* encoded = dict.FindString(base::ToLowerASCII(email));
  if (!encoded || encoded->empty()) {
    return std::string();
  }
  std::string encrypted;
  std::string plain;
  if (!base::Base64Decode(*encoded, &encrypted) ||
      !OSCrypt::DecryptString(encrypted, &plain)) {
    LOG(WARNING) << "[WINGS8OS] Failed to decrypt saved password";
    return std::string();
  }
  return plain;
}

void SaveWings8VaultSecret(PrefService* local_state,
                         const std::string& email,
                         const std::string& secret) {
  if (!local_state || email.empty() || secret.empty()) {
    return;
  }
  std::string encrypted;
  if (!OSCrypt::EncryptString(secret, &encrypted)) {
    LOG(ERROR) << "[WINGS8OS] Failed to encrypt vault secret";
    return;
  }
  ScopedDictPrefUpdate update(local_state, kWings8OsVaultSecrets);
  update->Set(base::ToLowerASCII(email), base::Base64Encode(encrypted));
}

std::string GetWings8VaultSecret(PrefService* local_state,
                               const std::string& email) {
  if (!local_state || email.empty()) {
    return std::string();
  }
  const base::Value::Dict& dict = local_state->GetDict(kWings8OsVaultSecrets);
  const std::string* encoded = dict.FindString(base::ToLowerASCII(email));
  if (!encoded || encoded->empty()) {
    return std::string();
  }
  std::string encrypted;
  std::string plain;
  if (!base::Base64Decode(*encoded, &encrypted) ||
      !OSCrypt::DecryptString(encrypted, &plain)) {
    LOG(WARNING) << "[WINGS8OS] Failed to decrypt vault secret";
    return std::string();
  }
  return plain;
}

}  // namespace prefs
}  // namespace wings8os
