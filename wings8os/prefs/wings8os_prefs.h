// Copyright (c) 2021 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_PREFS_H_
#define CHROMEOS_WINGS8OS_PREFS_H_

#include <string>

#include "wings8os/prefs/wings8os_pref_names.h"

class PrefRegistrySimple;
class PrefService;

namespace wings8os {

namespace prefs {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
void RegisterProfilePrefs(PrefRegistrySimple* registry);

void KeepCurrentPrefs(PrefService* local_state);
void SetNotNecessaryForceTpmFallback(PrefService* local_state);

void ClearRebootMarkPrefs(PrefService* local_state);
void ClearOneShotProfilePrefs(PrefService* prefs);

// Stores (OSCrypt-encrypted) the password that currently unlocks `email`'s
// cryptohome, so it can later be used to re-seal the cryptohome key without
// asking the user for their old password.
void SaveWings8AccountPassword(PrefService* local_state,
                             const std::string& email,
                             const std::string& password);

// Returns the last saved password for `email`, or an empty string if none.
std::string GetWings8AccountPassword(PrefService* local_state,
                                   const std::string& email);

// Stores (OSCrypt-encrypted) the random per-account vault secret used to seal
// a Wings8 ONLINE account's cryptohome (see osLogin / pod login).
void SaveWings8VaultSecret(PrefService* local_state,
                         const std::string& email,
                         const std::string& secret);

// Returns the stored vault secret for `email`, or an empty string if none.
std::string GetWings8VaultSecret(PrefService* local_state,
                               const std::string& email);

} // prefs

} // wings8os
#endif /* ifndef WINGS8OS_PREFS_H */
