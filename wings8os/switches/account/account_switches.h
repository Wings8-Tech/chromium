// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_ACCOUNT_SWITCHES_H_
#define CHROMEOS_WINGS8OS_SWITCHES_ACCOUNT_SWITCHES_H_

#include <string>
#include "chromeos/chromeos_export.h"

namespace wings8os {
namespace switches {

CHROMEOS_EXPORT bool IsWings8AccountEnabled();
CHROMEOS_EXPORT bool IsWings8ExtendAccountEnabled();

CHROMEOS_EXPORT extern const char kWings8AccountEnable[];
CHROMEOS_EXPORT extern const char kWings8AccountForceDisabledForTest[];

CHROMEOS_EXPORT extern const char kWings8OSGaiaUrl[];
CHROMEOS_EXPORT extern const char kWings8OSApisUrl[];
CHROMEOS_EXPORT extern const char kWings8OSDeviceManagementUrl[];
CHROMEOS_EXPORT extern const char kWings8OSRealtimeReportingUrl[];
CHROMEOS_EXPORT extern const char kWings8OSEncryptedReportingUrl[];
CHROMEOS_EXPORT extern const char kWings8OSSyncServiceURL[];
extern std::string GetWings8OSKidsManagementAPIBaseUrl();
CHROMEOS_EXPORT int GetWings8OSSupervisedUserSettingsSyncInterval();
CHROMEOS_EXPORT bool IsPolicyManagedByWings8();

bool IsWings8DMServerUrl(const std::string& url);

CHROMEOS_EXPORT std::string GetWings8FtlServerEndpoint();
CHROMEOS_EXPORT std::string GetWings8RemotingServerEndpoint();

}
}

#endif
