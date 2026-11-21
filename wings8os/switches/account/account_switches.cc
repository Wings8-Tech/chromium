// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/account/account_switches.h"
#include "wings8os/switches/account/account_constants.h"
#include "base/command_line.h"

namespace wings8os {
namespace switches {

namespace {

const char kWings8OSFamilyLinkApisUrl[] = "wings8os-family-link-apis-url";
const char kWings8OSSupervisedUserSettingsSyncIntervalInSeconds[] = "wings8os-supervised-user-settings-sync-interval";

const char kPolicyManagedByWings8[] = "policy-managed-by-wings8";

const char kWings8FtlServerEndpointSwitch[] = "wings8-ftl-server-endpoint";
const char kWings8RemotingServerEndpointSwitch[] = "wings8-remoting-server-endpoint";
}

bool IsWings8AccountEnabled() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  return command_line->HasSwitch(kWings8AccountEnable) && !command_line->HasSwitch(kWings8AccountForceDisabledForTest);
}

const char kWings8AccountEnable[] = "wings8-account-enabled";
const char kWings8AccountForceDisabledForTest[] = "wings8-account-force-disabled";

bool IsWings8ExtendAccountEnabled() {
  return IsWings8AccountEnabled();
}

const char kWings8OSGaiaUrl[] = "wings8os-gaia-url";
const char kWings8OSApisUrl[] = "wings8os-apis-url";
const char kWings8OSDeviceManagementUrl[] = "wings8os-device-management-url";
const char kWings8OSRealtimeReportingUrl[] = "wings8os-realtime-reporting-url";
const char kWings8OSEncryptedReportingUrl[] = "wings8os-encrypted-reporting-url";
const char kWings8OSSyncServiceURL[] = "wings8os-sync-url";

std::string GetWings8OSKidsManagementAPIBaseUrl() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(kWings8OSFamilyLinkApisUrl)) {
    return command_line->GetSwitchValueASCII(kWings8OSFamilyLinkApisUrl);
  } else {
    return std::string(wings8os::constants::kDefaultWings8OSFamilyLinkApisUrl);
  }
}

int GetWings8OSSupervisedUserSettingsSyncInterval() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  int interval = 0;
  if (command_line->HasSwitch(kWings8OSSupervisedUserSettingsSyncIntervalInSeconds)) {
    std::string str = command_line->GetSwitchValueASCII(kWings8OSSupervisedUserSettingsSyncIntervalInSeconds);
    interval = std::stoi(str);
  }
  return interval < 10 ? wings8os::constants::kWings8OSSupervisedUserSettingsDefaultSyncIntervalInSeconds : interval;
}

bool IsPolicyManagedByWings8() {
  // Wings8 accounts are enterprise-managed through the Wings8 SaaS (the device
  // management flow works when the DM backend is reachable). The login
  // black screen was caused by the OAuth2 session-restore termination, not
  // by the DM policy path — keep the original behavior.
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
             kPolicyManagedByWings8) ||
         IsWings8AccountEnabled();
}

bool IsWings8DMServerUrl(const std::string& url) {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(wings8os::switches::kWings8OSDeviceManagementUrl)) {
    return url == command_line->GetSwitchValueASCII(wings8os::switches::kWings8OSDeviceManagementUrl);
  } else {
    return url == wings8os::constants::kDefaultWings8OSDeviceManagementServerUrl;
  }
}


std::string GetWings8FtlServerEndpoint() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(wings8os::switches::kWings8FtlServerEndpointSwitch)) {
    return command_line->GetSwitchValueASCII(wings8os::switches::kWings8FtlServerEndpointSwitch);
  } else {
    return wings8os::constants::kDefaultWings8FtlServerEndpoint;
  }
}

std::string GetWings8RemotingServerEndpoint() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(wings8os::switches::kWings8RemotingServerEndpointSwitch)) {
    return command_line->GetSwitchValueASCII(wings8os::switches::kWings8RemotingServerEndpointSwitch);
  } else {
    return wings8os::constants::kDefaultWings8RemotingServerEndpoint;
  }
}


}// namespace switches
}// namespace wings8os
