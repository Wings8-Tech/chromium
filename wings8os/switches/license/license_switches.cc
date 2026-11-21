// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/license/license_switches.h"
#include "base/command_line.h"
#include "wings8os/switches/license/license_constants.h"

namespace wings8os {
namespace switches {

namespace {

const char kLicenseTestMode[] = "wings8os-license-test-mode";
const char kWings8OSLicenseWebUrl[] = "wings8os-license-web-url";
const char kWings8OSLicenseApiUrl[] = "wings8os-license-api-url";

}

bool IsLicenseTestMode() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kLicenseTestMode);
}

std::string GetWings8OSLicenseWebUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSLicenseWebUrl)) {
    return command_line->GetSwitchValueASCII(kWings8OSLicenseWebUrl);
  } else {
    return std::string(wings8os::constants::kDefaultWings8OSLicenseWebUrl);
  }
}

std::string GetWings8OSLicenseApiUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSLicenseApiUrl)) {
    return command_line->GetSwitchValueASCII(kWings8OSLicenseApiUrl);
  } else {
    return std::string(wings8os::constants::kDefaultWings8OSLicenseApiUrl);
  }
}

} // switches
} // wings8os
