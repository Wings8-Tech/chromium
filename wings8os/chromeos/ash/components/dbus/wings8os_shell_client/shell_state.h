// Copyright (c) 2018 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_DBUS_SHELL_STATE_H_
#define WINGS8OS_DBUS_SHELL_STATE_H_

#include <stdint.h>

#include <string>

#include "chromeos/chromeos_export.h"

namespace wings8os {
namespace ash {

struct CHROMEOS_EXPORT ShellState {
  int32_t code;
  std::string result;

  ShellState();
  std::string ToString() const;
};

}

}  // namespace wings8os

#endif  // WINGS8OS_DBUS_SHELL_STATE_H_
