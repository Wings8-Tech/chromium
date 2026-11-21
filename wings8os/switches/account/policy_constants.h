// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
#ifndef CHROMEOS_WINGS8OS_SWITCHES_ACCOUNT_POLICY_CONSTANTS_H_
#define CHROMEOS_WINGS8OS_SWITCHES_ACCOUNT_POLICY_CONSTANTS_H_

#include <string>
#include "chromeos/chromeos_export.h"

namespace wings8os {
namespace constants {

CHROMEOS_EXPORT extern const uint8_t kWings8OSPolicyVerificationKey[];
extern const size_t kWings8OSPolicyVerificationKeyLength;

inline constexpr char kWings8OSPolicyFCMInvalidationSenderID[] = "384261808202";

extern const char kWings8OSOobeZteConfigFile[];
}
}

#endif
