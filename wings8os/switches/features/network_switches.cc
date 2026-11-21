// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/features/network_switches.h"
#include "base/command_line.h"

namespace wings8os {
namespace switches {

namespace {

const char kResetWifiDriver[] = "wings8os-reset-wifi-driver";

}

bool NeedResetWifiDriver() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kResetWifiDriver);
}

} // switches
} // wings8os

