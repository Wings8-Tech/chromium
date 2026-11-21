// Copyright 2024 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_CONSTANTS_WINGS8OS_CONSTANTS_H_
#define WINGS8OS_CONSTANTS_WINGS8OS_CONSTANTS_H_

#include "wings8os/build/config/buildflags.h"
#include <string>

namespace wings8os::constants {

#if BUILDFLAG(USE_WINGS8OS_LICENSE)

enum class LicenseStateType {
  kUnspecified = 0,
  kUnlicensed = 1,
  kLicenseForYouTrial = 2 ,
  kLicenseForYouValid = 3,
  kLicenseForYouExpired = 4,
  kLicenseForEnterpriseTrial = 5,
  kLicenseForEnterpriseValid = 6,
  kLicenseForEnterpriseExpired = 7,
  kMaxValue = kLicenseForEnterpriseExpired,
};

enum class LicenseEnforcementLevel {
  kNone = 0,
  kForcePopup = 1,
  kForceQuit = 2,
  kMaxValue = kForceQuit,
};

#endif

bool ShouldHideExtensionById(const std::string& extension_id);

} // namespace wings8os::constants

#endif // !WINGS8OS_CONSTANTS_WINGS8OS_CONSTANTS_H_
