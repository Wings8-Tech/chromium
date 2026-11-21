// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_ACCELEROMETER_SWITCHES_H_
#define CHROMEOS_WINGS8OS_SWITCHES_ACCELEROMETER_SWITCHES_H_

#include "chromeos/chromeos_export.h"

namespace wings8os {
namespace switches {

CHROMEOS_EXPORT bool IsWings8OSAccelerometer();
CHROMEOS_EXPORT int GetAccelConfig();
CHROMEOS_EXPORT bool IsAccelRevertX();
CHROMEOS_EXPORT bool IsAccelRevertY();
CHROMEOS_EXPORT bool IsAccelRevertZ();
CHROMEOS_EXPORT bool IsAccelRightMove();
CHROMEOS_EXPORT int GetAccelRightMoveBits();
CHROMEOS_EXPORT int GetAccelDataPattern();
CHROMEOS_EXPORT bool IsRotate_90();
CHROMEOS_EXPORT bool IsRotate_180();
CHROMEOS_EXPORT bool IsRotate_270();
CHROMEOS_EXPORT int GetWings8OSAccelerometerReadIntervalInMS();
CHROMEOS_EXPORT bool Wings8OSAccelerometerSwapBytes();

} // switches
} // wings8os
#endif
