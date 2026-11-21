// Copyright 2026 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_WEB_APPLICATIONS_PREINSTALLED_WEB_APPS_WINGS8_SAAS_H_
#define CHROME_BROWSER_WEB_APPLICATIONS_PREINSTALLED_WEB_APPS_WINGS8_SAAS_H_

#include "chrome/browser/web_applications/external_install_options.h"

namespace web_app {

// Wings8 SaaS portal (fleet, seats, billing). Premium bundle: Pro/Pro+ only.
ExternalInstallOptions GetConfigForWings8Saas();

}  // namespace web_app

#endif  // CHROME_BROWSER_WEB_APPLICATIONS_PREINSTALLED_WEB_APPS_WINGS8_SAAS_H_
