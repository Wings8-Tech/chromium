// Copyright 2024 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/constants/wings8os_constants.h"

namespace wings8os::constants {

namespace {

const char kWings8SystemControllerExtensionId[] = "mofiofjpikncjaigmdlblhojbnkabako";
const char kWings8RdpExtensionId[] = "fogdcaodknbhigpklbhepedofamkfbln";

constexpr char const* kExtensionIdsHiddenInList[] = {
    kWings8SystemControllerExtensionId,
    kWings8RdpExtensionId,
};

}

bool ShouldHideExtensionById(const std::string& extension_id) {
  for (auto* const id : kExtensionIdsHiddenInList) {
    if (id == extension_id) {
      return true;
    }
  }
  return false;
}

} // namespace wings8os::constants
