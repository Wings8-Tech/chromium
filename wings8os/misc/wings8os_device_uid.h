// Copyright (c) 2026 The Wings8 OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_MISC_WINGS8OS_DEVICE_UID_H_
#define WINGS8OS_MISC_WINGS8OS_DEVICE_UID_H_

#include <string>

class PrefService;

namespace wings8os {

// Retourne un identifiant unique et stable par appareil, respectueux de la
// vie privee : le resultat est un hash SHA-256, le numero de serie brut ne
// quitte jamais la machine. Ordre de priorite :
//   1. machine-id VPD ChromeOS (vrais Chromebooks / appareils avec VPD) ;
//   2. /var/lib/wings8os/device_uid (hash DMI ecrit au boot, survit a la
//      reinstallation) ;
//      lisible par l utilisateur chrome) ;
//   3. /var/lib/dbus/machine-id ou /etc/machine-id (stable par installation,
//      lisible par l utilisateur chrome) ;
//   4. UUID aleatoire persiste dans local state (pref wings8os.device_uid).
std::string GetDeviceUid(PrefService* local_state);

}  // namespace wings8os

#endif  // WINGS8OS_MISC_WINGS8OS_DEVICE_UID_H_