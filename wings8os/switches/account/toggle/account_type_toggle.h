// Copyright (c) 2022 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_SWITCHES_ACCOUNT_TOGGLE_ACCOUNT_TYPE_TOGGLE_H_
#define WINGS8OS_SWITCHES_ACCOUNT_TOGGLE_ACCOUNT_TYPE_TOGGLE_H_

#include "chromeos/chromeos_export.h"
#include <string>
#include <vector>

namespace base {
  class CommandLine;
}
class AccountId;

namespace wings8os {
namespace switches {

CHROMEOS_EXPORT void EnableWings8AccountFlag();
CHROMEOS_EXPORT void DisableWings8AccountFlag();
CHROMEOS_EXPORT void ToggleWings8AccountFlagByAccountId(const AccountId& account_id);
CHROMEOS_EXPORT void ToggleWings8AccountFlagForCommandLine(base::CommandLine* command_line);
CHROMEOS_EXPORT void ToggleWings8AccountFlagForCommandLineByAccountId(base::CommandLine* command_line, const AccountId& account_id);
CHROMEOS_EXPORT void ToggleWings8AccountFlagByActiveUser();
CHROMEOS_EXPORT void EnableWings8AccountFlagForManagedDevice();
CHROMEOS_EXPORT void DisableWings8AccountFlagForManagedDevice();
CHROMEOS_EXPORT void AppendAccountSwitchesIfNeed(const AccountId& account_id, std::vector<std::string>* switches);

} // namespace switches
} // namespace wings8os


#endif  // WINGS8OS_SWITCHES_ACCOUNT_TOGGLE_ACCOUNT_TYPE_TOGGLE_H_
