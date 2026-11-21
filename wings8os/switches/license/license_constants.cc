// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/license/license_constants.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os::constants {

#if BUILDFLAG(USE_WINGS8OS_COM)
const char kDefaultWings8OSLicenseWebUrl[] = "https://cashier.wings8.org";
const char kDefaultWings8OSLicenseApiUrl[] = "https://apis.wings8.org/license";
#else
const char kDefaultWings8OSLicenseWebUrl[] = "https://cashier.wings8.org";
const char kDefaultWings8OSLicenseApiUrl[] = "https://apis.wings8.org/license";
#endif

const char kWings8OSOEMTokenFilePath[] = "/usr/share/oem/wings8os_oem_token";

}  // namespace wings8os::constants
