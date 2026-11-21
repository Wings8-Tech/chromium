// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/display/display_switches.h"

#include "base/command_line.h"
#include <string>

namespace wings8os {
namespace switches {

namespace {

const char kDefaultDSF[] = "wings8os-default-dsf";
const char kScreenDpi[] = "wings8os-default-screen-dpi";

}

float GetDefaultDSF(float default_value) {
  std::string factorStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kDefaultDSF);
  if (factorStr.empty())
    return default_value;
  return std::stof(factorStr);
}

float GetDefaultScreenDpi(float default_value) {
  std::string factorStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kScreenDpi);
  if (factorStr.empty())
    return default_value;
  return std::stof(factorStr);
}

} // switches
} // wings8os

