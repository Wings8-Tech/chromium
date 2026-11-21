// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_SERVICES_CONSTANTS_H_
#define CHROMEOS_WINGS8OS_SWITCHES_SERVICES_CONSTANTS_H_

#include "chromeos/chromeos_export.h"
#include <string>

namespace wings8os {
namespace constants {

CHROMEOS_EXPORT extern const char kDefaultWings8OSGeolocationAPIUrl[];
CHROMEOS_EXPORT extern const char kDefaultWings8OSTimezoneAPIUrl[];

CHROMEOS_EXPORT extern const char kDefaultWings8OSLookingGlassUrl[];

CHROMEOS_EXPORT extern const char kWings8OSFeedbackPostUrl[];

CHROMEOS_EXPORT extern const uint8_t* kWings8OSCryptoKey;
extern const size_t kWings8OSCryptoKeyLength;

extern const char kWings8OSStoreAppId[];

CHROMEOS_EXPORT extern const char kWings8OSWebStoreUpdateURL[];

CHROMEOS_EXPORT extern const char kWings8OSAssistantDefaultWebUrl[];
} // constants
} // wings8os

#endif
