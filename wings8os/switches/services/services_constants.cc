// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/services/services_constants.h"
#include "wings8os/build/config/buildflags.h"
#include "wings8os/switches/account/policy_constants.h"

namespace wings8os::constants {

// ⚠️ IMPORTANT: These URLs are EXAMPLE PLACEHOLDERS ONLY and must be replaced
// with real, functional API endpoints before production deployment.
// These example URLs will NOT work and are provided for development/testing purposes.
#if BUILDFLAG(USE_WINGS8OS_COM)
const char kDefaultWings8OSGeolocationAPIUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/geo/locationByIp?"; // EXAMPLE - Replace with real geolocation API
const char kDefaultWings8OSTimezoneAPIUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/geo/timezone?"; // EXAMPLE - Replace with real timezone API
const char kDefaultWings8OSLookingGlassUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/lookingglass"; // EXAMPLE - Replace with real diagnostics service
const char kWings8OSWebStoreUpdateURL[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/store"; // EXAMPLE - Replace with real app store URL
const char kWings8OSFeedbackPostUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/feedback/submit"; // EXAMPLE - Replace with real feedback API

const char kWings8OSAssistantDefaultWebUrl[] = "https://ai.wings8.org/chat/";
#else
// URLs for Wings8OS services when using the .io domain
// ⚠️ IMPORTANT: These URLs are EXAMPLE PLACEHOLDERS ONLY and must be replaced
// with real, functional API endpoints before production deployment.
// These example URLs will NOT work and are provided for development/testing purposes.
const char kDefaultWings8OSGeolocationAPIUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/geo/locationByIp?"; // EXAMPLE - Replace with real geolocation API
const char kDefaultWings8OSTimezoneAPIUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/geo/timezone?"; // EXAMPLE - Replace with real timezone API
const char kDefaultWings8OSLookingGlassUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/lookingglass"; // EXAMPLE - Replace with real diagnostics service
const char kWings8OSWebStoreUpdateURL[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/store"; // EXAMPLE - Replace with real app store URL
const char kWings8OSFeedbackPostUrl[] =
  "https://l8rof5h3z7.execute-api.us-east-1.amazonaws.com/feedback/submit"; // EXAMPLE - Replace with real feedback API

const char kWings8OSAssistantDefaultWebUrl[] = "https://ai.wings8.org/chat/";
#endif

const uint8_t* kWings8OSCryptoKey =
  wings8os::constants::kWings8OSPolicyVerificationKey;
const size_t kWings8OSCryptoKeyLength =
  wings8os::constants::kWings8OSPolicyVerificationKeyLength;

const char kWings8OSStoreAppId[] = "hidnajblbifdkmheebalalchohohmaef";

}  // namespace wings8os::constants
