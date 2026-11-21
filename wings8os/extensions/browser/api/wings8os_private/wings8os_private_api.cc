// Copyright 2023 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/extensions/browser/api/wings8os_private/wings8os_private_api.h"
#include "wings8os/build/config/buildflags.h"
#include "base/command_line.h"
#include "wings8os/switches/misc/misc_switches.h"

namespace extensions {

ExtensionFunction::ResponseAction Wings8osPrivateGetWings8OSInfoFunction::Run() {
  base::Value::Dict result;
  // WINGS8OS: this suffix drives the sovereign remote-desktop endpoints used by
  // the preinstalled CRD webapp (accounts.<suffix>, apis.<suffix>/remoting/v1,
  // rtc.<suffix>:5443/bosh). Point it at our own infrastructure.
  std::string host_sufffux = "wings8.org";
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(
        wings8os::switches::kWings8OSServiceHostSuffixForTesting)) {
    host_sufffux = command_line->GetSwitchValueASCII(
        wings8os::switches::kWings8OSServiceHostSuffixForTesting);
  }
  result.Set("host_suffix", host_sufffux);
#if BUILDFLAG(IS_OPENWINGS8)
  result.Set("wings8os", false);
#else
  result.Set("wings8os", true);
#endif
  return RespondNow(WithArguments(std::move(result)));
}

}  // namespace extensions
