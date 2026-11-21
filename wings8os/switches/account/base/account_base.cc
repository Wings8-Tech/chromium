// Copyright (c) 2022 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/account/base/account_base.h"

namespace wings8os {
namespace switches {

namespace {
bool is_device_managed = false;
}

void Wings8SetDeviceManagedFlag(bool is_managed) {
  is_device_managed = is_managed;
}

bool IsWings8SetDeviceManaged() {
  return is_device_managed;
}

} // namespace switches
} // namespace wings8os
