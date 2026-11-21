// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_SERVICES_SWITCHES_H_
#define CHROMEOS_WINGS8OS_SWITCHES_SERVICES_SWITCHES_H_

#include <string>
#include "chromeos/chromeos_export.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os {
namespace switches {

CHROMEOS_EXPORT bool DisableWings8OSGeolocationAPI();
CHROMEOS_EXPORT bool DisableWings8OSTimezoneAPI();

extern std::string GetWings8OSGeolocationAPIUrl();
extern std::string GetWings8OSTimezoneAPIUrl();

extern std::string GetWings8OSLookingGlassUrl();

extern std::string GetWings8OSAppStoreURL();

extern std::string GetWings8OSWebStoreUpdateUrl();

extern std::string GetWings8OSAssistantWebUrl();

CHROMEOS_EXPORT std::string MayConvertWebStoreUpdateUrl(
    const std::string& url);

#if BUILDFLAG(WINGS8OS_DEVICE)
std::string GetWings8OSProductWarrantyUrl();
#endif

} // switches
} // wings8os

#endif
