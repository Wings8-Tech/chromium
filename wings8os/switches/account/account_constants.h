// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_WINGS8OS_SWITCHES_ACCOUNT_CONSTANTS_H_
#define CHROMEOS_WINGS8OS_SWITCHES_ACCOUNT_CONSTANTS_H_

#include <string>
#include "chromeos/chromeos_export.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os {
namespace constants {

CHROMEOS_EXPORT extern const char kDefaultWings8OSGaiaUrl[];
CHROMEOS_EXPORT extern const char kDefaultWings8OSApisBaseUrl[];
CHROMEOS_EXPORT extern const char kDefaultWings8OSDeviceManagementServerUrl[];
CHROMEOS_EXPORT extern const char kDefaultWings8OSRealtimeReportingServerUrl[];
CHROMEOS_EXPORT extern const char kDefaultWings8OSEncryptedReportingServerUrl[];
CHROMEOS_EXPORT extern const char kWings8OSSyncDevServerUrl[];
CHROMEOS_EXPORT extern const char kWings8OSSyncServerUrl[];

CHROMEOS_EXPORT extern const char kDefaultWings8OSFamilyLinkApisUrl[];

CHROMEOS_EXPORT extern const char kDefaultWings8FtlServerEndpoint[];
CHROMEOS_EXPORT extern const char kDefaultWings8RemotingServerEndpoint[];

extern const size_t kWings8OSSupervisedUserSettingsDefaultSyncIntervalInSeconds;

#if BUILDFLAG(IS_OPENWINGS8)
CHROMEOS_EXPORT extern const char kWings8APIKeysDevelopersHowToURL[];
#endif

CHROMEOS_EXPORT extern const char kWings8EnrollmentTokenFilePath[];
}//constants
}//wings8os

#endif
