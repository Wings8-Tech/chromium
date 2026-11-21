// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/services/services_switches.h"

#include "base/command_line.h"
#include "wings8os/switches/services/services_constants.h"
#include "wings8os/switches/urls/urls_constants.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os {
namespace switches {

namespace {

const char kDisableWings8OSGeolocationAPI[] = "disable-wings8os-geolocation-api";
const char kDisableWings8OSTimezoneAPI[] = "disable-wings8os-timezone-api";

const char kWings8OSGeolocationAPIUrl[] = "wings8os-geolocation-api-url";
const char kWings8OSTimezoneAPIUrl[] = "wings8os-timezone-api-url";

const char kWings8OSLookingGlassUrl[] = "wings8os-lookingglass-url";

const char kWings8OSAppsGalleryURL[] = "wings8os-apps-gallery-url";

const char kWings8OSAppsGalleryUpdateURL[] = "wings8os-apps-gallery-update-url";

const char kWings8OSAssistantWebUrl[] = "wings8os-ai-url";

const char kWings8OSStoreComPrefix[] = "https://store.wings8.org";
const char kWings8OSStoreIoPrefix[] = "https://chromewebstore.google.com";

#if BUILDFLAG(WINGS8OS_DEVICE)
const char kWings8OSProductWarrantyURL[] = "wings8os-product-warranty-url";
#endif

}

bool DisableWings8OSGeolocationAPI() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  return command_line->HasSwitch(kDisableWings8OSGeolocationAPI);
}

bool DisableWings8OSTimezoneAPI() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  return command_line->HasSwitch(kDisableWings8OSTimezoneAPI);
}

std::string GetWings8OSGeolocationAPIUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSGeolocationAPIUrl)) {
    return command_line->GetSwitchValueASCII(kWings8OSGeolocationAPIUrl);
  } else {
    return std::string(wings8os::constants::kDefaultWings8OSGeolocationAPIUrl);
  }
}

std::string GetWings8OSTimezoneAPIUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSTimezoneAPIUrl)) {
    return command_line->GetSwitchValueASCII(kWings8OSTimezoneAPIUrl);
  } else {
    return std::string(wings8os::constants::kDefaultWings8OSTimezoneAPIUrl);
  }
}

std::string GetWings8OSLookingGlassUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSLookingGlassUrl)) {
    return command_line->GetSwitchValueASCII(kWings8OSLookingGlassUrl);
  } else {
    return std::string(wings8os::constants::kDefaultWings8OSLookingGlassUrl);
  }
}

std::string GetWings8OSAppStoreURL() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSAppsGalleryURL)) {
    return command_line->GetSwitchValueASCII(kWings8OSAppsGalleryURL);
  } else {
    return std::string(wings8os::constants::kWings8OSStoreBaseUrl);
  }
}

std::string GetWings8OSWebStoreUpdateUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSAppsGalleryUpdateURL)) {
    return command_line->GetSwitchValueASCII(kWings8OSAppsGalleryUpdateURL);
  } else {
    return std::string(wings8os::constants::kWings8OSWebStoreUpdateURL);
  }
}

std::string GetWings8OSAssistantWebUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSAssistantWebUrl)) {
    std::string value(command_line->GetSwitchValueASCII(kWings8OSAssistantWebUrl));
    if (!value.empty()) {
      return value;
    }
  }
  return std::string(wings8os::constants::kWings8OSAssistantDefaultWebUrl);
}

CHROMEOS_EXPORT std::string MayConvertWebStoreUpdateUrl(
    const std::string& url) {
  std::string new_url = url;
#if BUILDFLAG(USE_WINGS8OS_COM)
  if (new_url.find(kWings8OSStoreIoPrefix) == 0) {
    new_url.replace(0, sizeof(kWings8OSStoreIoPrefix) - 1,
                    kWings8OSStoreComPrefix);
  }
#else
  if (new_url.find(kWings8OSStoreComPrefix) == 0) {
    new_url.replace(0, sizeof(kWings8OSStoreComPrefix) - 1,
                    kWings8OSStoreIoPrefix);
  }
#endif
  return new_url;
}

#if BUILDFLAG(WINGS8OS_DEVICE)
std::string GetWings8OSProductWarrantyUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSProductWarrantyURL)) {
    return command_line->GetSwitchValueASCII(kWings8OSProductWarrantyURL);
  } else {
    return std::string(wings8os::constants::kWings8OSProductWarrantyDefaultURL);
  }
}
#endif

} // switches
} // wings8os
