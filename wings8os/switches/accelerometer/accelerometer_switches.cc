// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/accelerometer/accelerometer_switches.h"
#include "base/command_line.h"

namespace wings8os {
namespace switches {

namespace {

const char kAccelConfigIndex[] = "wings8os-accel-config";
const char kAccelRevertX[] = "wings8os-accel-revert-x";
const char kAccelRevertY[] = "wings8os-accel-revert-y";
const char kAccelRevertZ[] = "wings8os-accel-revert-z";
const char kAccelRightMoveBits[] = "wings8os-accel-right-move";
const char kAccelDataPattern[] = "wings8os-accel-pattern";
const char kRotate_90[] = "wings8os-rotate-90";
const char kRotate_180[] = "wings8os-rotate-180";
const char kRotate_270[] = "wings8os-rotate-270";
const char kWings8OSAccelerometerReadInterval[] = "wings8os-accel-read-interval";
const char kWings8OSAccelerometerSwapBytes[] = "wings8os-accel-swap-bytes";

}

bool IsWings8OSAccelerometer() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kAccelConfigIndex);
}

int GetAccelConfig() {
  std::string indexStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kAccelConfigIndex);
  if (indexStr.empty())
    return 0;
  return std::stoi(indexStr);
}

bool IsAccelRevertX() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kAccelRevertX);
}

bool IsAccelRevertY() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kAccelRevertY);
}

bool IsAccelRevertZ() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kAccelRevertZ);
}

bool IsAccelRightMove() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kAccelRightMoveBits);
}

int GetAccelRightMoveBits() {
  int ret = 0;
  if (IsAccelRightMove()) {
    ret = 4;
    std::string rightBitsStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kAccelRightMoveBits);
    if (!rightBitsStr.empty())
      ret = std::stoi(rightBitsStr);
  }
  return ret;
}

int GetAccelDataPattern() {
  std::string patternStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kAccelDataPattern);
  if (patternStr.empty())
    return 0;
  return std::stoi(patternStr);
}

bool IsRotate_90(){
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kRotate_90);
}

bool IsRotate_180(){
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kRotate_180);
}

bool IsRotate_270(){
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kRotate_270);
}

int GetWings8OSAccelerometerReadIntervalInMS() {
  std::string patternStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kWings8OSAccelerometerReadInterval);
  if (patternStr.empty())
    return 0;
  return std::stoi(patternStr);
}

bool Wings8OSAccelerometerSwapBytes() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(kWings8OSAccelerometerSwapBytes);
}

} // switches
} // wings8os
