# Wings8OS Preinstalled Web Apps (PWAs)

This directory contains the C++ configuration files for preinstalled PWAs in Wings8OS.

## Overview

Wings8OS uses the hardcoded C++ approach to preinstall PWAs. This is the most robust method, as it compiles the PWA configurations directly into Chrome, ensuring they are always installed on first boot regardless of network conditions or policy settings.

## How It Works

1. Each PWA has a header file (`.h`) and implementation file (`.cc`)
2. The implementation file defines a `GetConfigFor*()` function that returns an `ExternalInstallOptions` struct
3. These functions are called from `chrome/browser/web_applications/preinstalled_web_apps/preinstalled_web_apps.cc`
4. The source files are compiled via `chrome/browser/web_applications/BUILD.gn`

## Preinstalled PWAs

| App | URL | Function | Folder |
|-----|-----|----------|--------|
| Wings8OS Community | https://community.wings8os.io/ | `GetConfigForWings8Community()` | Root |
| Wings8OS Remote Desktop | https://remotedesktop.wings8.org/ | `GetConfigForWings8RemoteDesktop()` | Root |
| Wings8OS Notes | https://note.wings8.org/ | `GetConfigForWings8Notes()` | **OEM/WINGS8** |
| Mistral AI | https://chat.mistral.ai/chat | `GetConfigForMistral()` | Root |
| Qwant | https://www.qwant.com/?l=fr | `GetConfigForQwant()` | Root |
| Calculator | https://calculator.apps.chrome/ | `GetConfigForWings8Calculator()` | Root |
| Galerie | https://galerie-eta.vercel.app/ | `GetConfigForGalerie()` | Root |
| Osivibe | https://osivibe.wings8.org/ | `GetConfigForOsivibe()` | **OEM/WINGS8** |
| Nephtys | https://nephtys.wings8.org/auth | `GetConfigForNephtys()` | **OEM/WINGS8** |
| Wings8Chess | https://chess.wings8.org/ | `GetConfigForWings8Chess()` | **OEM/WINGS8** |
| SetSound | https://setsound.wings8.org/ | `GetConfigForSetSound()` | **OEM/WINGS8** |
| Anima | https://anima.wings8.org/ | `GetConfigForAnima()` | **OEM/WINGS8** |
| Wings8PDF | https://pdf.wings8.org/ | `GetConfigForWings8PDF()` | **OEM/WINGS8** |
| QuickText | https://quicktext.wings8.org/ | `GetConfigForQuickText()` | **OEM/WINGS8** |
| Gmail | https://mail.google.com/ | `GetConfigForWings8Gmail()` | Root |
| Text Editor | https://text.app/ | `GetConfigForWings8Text()` | Root |
| Office 365 | https://www.office.com/?auth=1 | `GetConfigForOffice365()` | Root |
| ToffeeShare | https://toffeeshare.com/ | `GetConfigForToffeeShare()` | Root |
| Excalidraw | https://excalidraw.com/ | `GetConfigForExcalidraw()` | Root |
| VS Code | https://vscode.dev/ | `GetConfigForVSCode()` | Root |
| WhatsApp | https://web.whatsapp.com/ | `GetConfigForWhatsApp()` | Root |
| Teams | https://teams.microsoft.com/ | `GetConfigForTeams()` | Root |
| Google Docs | https://docs.google.com/ | `GetConfigForWings8Docs()` | Root |
| Google Sheets | https://docs.google.com/spreadsheets | `GetConfigForWings8Sheets()` | Root |
| Google Meet | https://meet.google.com/ | `GetConfigForWings8Meet()` | Root |

## Adding a New PWA

### Step 1: Create Header File

Create `newapp.h` in `chrome/browser/web_applications/preinstalled_web_apps/`:

```cpp
// Copyright 2025 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_WEB_APPLICATIONS_PREINSTALLED_WEB_APPS_NEWAPP_H_
#define CHROME_BROWSER_WEB_APPLICATIONS_PREINSTALLED_WEB_APPS_NEWAPP_H_

#include "chrome/browser/web_applications/external_install_options.h"

namespace web_app {

ExternalInstallOptions GetConfigForNewApp();

}  // namespace web_app

#endif  // CHROME_BROWSER_WEB_APPLICATIONS_PREINSTALLED_WEB_APPS_NEWAPP_H_
```

### Step 2: Create Implementation File

Create `newapp.cc` in `chrome/browser/web_applications/preinstalled_web_apps/`:

```cpp
// Copyright 2025 Wings8 Technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/web_applications/preinstalled_web_apps/newapp.h"

namespace web_app {

ExternalInstallOptions GetConfigForNewApp() {
  ExternalInstallOptions options(
      /*install_url=*/GURL("https://example.com/"),
      /*user_display_mode=*/mojom::UserDisplayMode::kStandalone,
      /*install_source=*/ExternalInstallSource::kExternalDefault);

  options.user_type_allowlist = {"unmanaged", "managed", "child"};
  options.add_to_quick_launch_bar = false;
  
  // Set to true to put in OEM folder, false for Root
  options.oem_installed = true; 

  return options;
}

}  // namespace web_app
```

### Step 3: Update preinstalled_web_apps.cc

In `chrome/browser/web_applications/preinstalled_web_apps/preinstalled_web_apps.cc`:

1. Add the include at the top:
```cpp
#include "chrome/browser/web_applications/preinstalled_web_apps/newapp.h"
```

2. Add the function call in `GetChromeBrandedApps` (for branded builds) AND `GetPreinstalledWebApps` (for non-branded builds):
```cpp
// In GetChromeBrandedApps:
return {
  // ...
  GetConfigForNewApp(),
};

// In GetPreinstalledWebApps (#else block):
return {
  // ...
  GetConfigForNewApp(),
};
```

### Step 4: Update BUILD.gn

In `chrome/browser/web_applications/BUILD.gn`, add the source files:

```gn
sources += [
  // ... other Wings8OS files ...
  "preinstalled_web_apps/newapp.cc",
  "preinstalled_web_apps/newapp.h",
]
```

### Step 5: Rebuild Chrome

```bash
cros_sdk
emerge-amd64-wings8os chromeos-chrome
```
