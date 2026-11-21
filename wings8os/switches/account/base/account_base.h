// Copyright (c) 2022 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_SWITCHES_ACCOUNT_ACCOUNT_BASE_H_
#define WINGS8OS_SWITCHES_ACCOUNT_ACCOUNT_BASE_H_

#include "chromeos/chromeos_export.h"

namespace wings8os {
namespace switches {

CHROMEOS_EXPORT void Wings8SetDeviceManagedFlag(bool is_managed);
CHROMEOS_EXPORT bool IsWings8SetDeviceManaged();

} // namespace switches
} // namespace wings8os


#endif  // WINGS8OS_SWITCHES_ACCOUNT_ACCOUNT_BASE_H_
