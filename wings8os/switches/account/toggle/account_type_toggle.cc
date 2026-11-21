// Copyright (c) 2022 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/account/toggle/account_type_toggle.h"
#include "wings8os/switches/account/account_switches.h"
#include "wings8os/switches/account/base/account_base.h"

#include "google_apis/gaia/gaia_urls.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/policy/chrome_browser_policy_connector.h"
#include "chrome/browser/browser_process_platform_part_chromeos.h"
#include "components/user_manager/user_manager.h"
#include "components/account_id/account_id.h"
#include "base/command_line.h"
#include "remoting/base/service_urls.h"


namespace wings8os {
namespace switches {

namespace {

void ResetUrls() {
  GaiaUrls *gaia_urls = GaiaUrls::GetInstance();
  if (gaia_urls) {
    gaia_urls->Reset();
  }

  remoting::ServiceUrls* service_urls = remoting::ServiceUrls::GetInstance();
  if (service_urls) {
    service_urls->ResetServerEndpoints();
  }

  if (!g_browser_process || !g_browser_process->platform_part()) return;
  policy::ChromeBrowserPolicyConnector* connector =
      g_browser_process->browser_policy_connector();
  if (connector) {
    connector->ResetDeviceManagementServiceConfiguration();
  }
}

void ToggleWings8AccountFlagInternal(base::CommandLine* cmdline, const AccountType account_type) {
  if (cmdline->HasSwitch(kWings8AccountForceDisabledForTest)) return;
  if (IsWings8SetDeviceManaged()) return;
  bool need_reset_url = false;
  if (account_type == AccountType::WINGS8_ACCOUNT) {
    if (!cmdline->HasSwitch(kWings8AccountEnable)) {
      cmdline->AppendSwitch(kWings8AccountEnable);
      need_reset_url = true;
    }
  } else if (account_type == AccountType::GOOGLE) {
    if (cmdline->HasSwitch(kWings8AccountEnable)) {
      cmdline->RemoveSwitch(kWings8AccountEnable);
      need_reset_url = true;
    }
  } else {
    return;
  }

  if (need_reset_url) {
    ResetUrls();
  }
}

user_manager::User* GetActiveUserInternal() {
  if (!user_manager::UserManager::IsInitialized()) { return nullptr; }
  user_manager::UserManager* user_manager_ = user_manager::UserManager::Get();
  if (!user_manager_) { return nullptr; }
  user_manager::User* user = user_manager_->GetActiveUser();
  return user;
}

}

void ToggleWings8AccountFlagByAccountId(const AccountId& account_id) {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  ToggleWings8AccountFlagInternal(command_line, account_id.GetAccountType());
}

void ToggleWings8AccountFlagForCommandLine(base::CommandLine* command_line) {
  user_manager::User* user = GetActiveUserInternal();
  if (!user) return;
  AccountId account_id = user->GetAccountId();
  ToggleWings8AccountFlagInternal(command_line, account_id.GetAccountType());
}

void ToggleWings8AccountFlagForCommandLineByAccountId(base::CommandLine* command_line, const AccountId& account_id) {
  ToggleWings8AccountFlagInternal(command_line, account_id.GetAccountType());
}

void EnableWings8AccountFlag() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  ToggleWings8AccountFlagInternal(command_line, AccountType::WINGS8_ACCOUNT);
}

void DisableWings8AccountFlag() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  ToggleWings8AccountFlagInternal(command_line, AccountType::GOOGLE);
}

void ToggleWings8AccountFlagByActiveUser() {
  user_manager::User* user = GetActiveUserInternal();
  if (!user) return;
  ToggleWings8AccountFlagByAccountId(user->GetAccountId());
}

void EnableWings8AccountFlagForManagedDevice() {
  EnableWings8AccountFlag();
  Wings8SetDeviceManagedFlag(true);
}

void DisableWings8AccountFlagForManagedDevice() {
  DisableWings8AccountFlag();
  Wings8SetDeviceManagedFlag(true);
}

void AppendAccountSwitchesIfNeed(const AccountId& account_id, std::vector<std::string>* switches) {
  // GetSwitchString
  base::CommandLine cmd_line(base::CommandLine::NO_PROGRAM);
  cmd_line.AppendSwitch(kWings8AccountEnable);
  const std::string account_switch = cmd_line.argv()[1];

  if (account_id.GetAccountType() == AccountType::WINGS8_ACCOUNT && std::find(switches->begin(), switches->end(), account_switch) == switches->end()) {
    switches->push_back(account_switch);
  }
}

} // namespace switches
} // namespace wings8os
