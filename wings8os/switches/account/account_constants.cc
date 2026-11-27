// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/account/account_constants.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os::constants {

#if BUILDFLAG(USE_WINGS8OS_COM)

const char kDefaultWings8OSGaiaUrl[] = "https://auth-app.wings8tech.com/8ab03d25-4808-4e5e-bf86-c9739f5b65eb";
const char kDefaultWings8OSApisBaseUrl[] = "https://auth-app.wings8tech.com/8ab03d25-4808-4e5e-bf86-c9739f5b65eb";
const char kDefaultWings8OSDeviceManagementServerUrl[] = "https://auth-app.wings8tech.com/8ab03d25-4808-4e5e-bf86-c9739f5b65eb/devicemanagement";
const char kDefaultWings8OSRealtimeReportingServerUrl[] =
  "https://apis.wings8.org/report/events";
const char kDefaultWings8OSEncryptedReportingServerUrl[] =
  "https://apis.wings8.org/report/record";
const char kWings8OSSyncDevServerUrl[] = "https://auth-app.wings8tech.com/8ab03d25-4808-4e5e-bf86-c9739f5b65eb/chrome-sync";
const char kWings8OSSyncServerUrl[] = "https://auth-app.wings8tech.com/8ab03d25-4808-4e5e-bf86-c9739f5b65eb/chrome-sync";
const char kDefaultWings8OSFamilyLinkApisUrl[] =
  "https://familylink-apis.wings8.org/kidsmanagement/v1/";

const char kDefaultWings8FtlServerEndpoint[] = "im.wings8.org";
const char kDefaultWings8RemotingServerEndpoint[] = "remoting.wings8.org";

#else

const char kDefaultWings8OSGaiaUrl[] = "https://auth-app.wings8tech.com/8ab03d25-4808-4e5e-bf86-c9739f5b65eb";
const char kDefaultWings8OSApisBaseUrl[] = "https://apis.wings8.org";
const char kDefaultWings8OSDeviceManagementServerUrl[] =
  "https://policy.wings8.org";
const char kDefaultWings8OSRealtimeReportingServerUrl[] =
  "https://apis.wings8.org/report/events";
const char kDefaultWings8OSEncryptedReportingServerUrl[] =
  "https://apis.wings8.org/report/record";
const char kWings8OSSyncDevServerUrl[] =
  "https://clients4.wings8.org/chrome-sync/dev";
const char kWings8OSSyncServerUrl[] = "https://clients4.wings8.org/chrome-sync";
const char kDefaultWings8OSFamilyLinkApisUrl[] =
  "https://familylink-apis.wings8.org/kidsmanagement/v1/";

const char kDefaultWings8FtlServerEndpoint[] = "im.wings8.org";
const char kDefaultWings8RemotingServerEndpoint[] = "remoting.wings8.org";

#endif

const size_t kWings8OSSupervisedUserSettingsDefaultSyncIntervalInSeconds = 600;
const char kWings8EnrollmentTokenFilePath[] =
  "/usr/share/oem/wings8os_enroll_token";

#if BUILDFLAG(IS_OPENWINGS8)
const char kWings8APIKeysDevelopersHowToURL[] =
  "https://openwings8.com/docs/developers/how-to-get-api-keys";
#endif

}  // namespace wings8os::constants
