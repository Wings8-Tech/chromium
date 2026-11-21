// Copyright 2024 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/misc/wings8os_dev_mode.h"
#include "base/files/file_util.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include "base/logging.h"
#include "wings8os/chromeos/ash/components/dbus/wings8os_shell_client/wings8os_shell_client.h"

using wings8os::ash::Wings8OSShellClient;
using wings8os::ash::ShellState;

namespace wings8os::misc {

namespace {

Wings8OSShellClient* GetShellClient() {
  return Wings8OSShellClient::Get();
}
const char bin_script[] = "/usr/sbin/crossystem_mode-switch.sh";
const char enable_param[] = "enable-dev_mode";
const char disable_param[] = "disable-dev_mode";
const char query_param[] = "dev_mode";

void OnSetCommandFinished(const bool enabled, base::OnceCallback<void(bool)> callback, std::optional<ShellState> state) {
  if (!state || state->code != 0) {
    LOG(ERROR) << "Set dev mode " << enabled << " failed";
    std::move(callback).Run(false);
    return;
  }
  std::move(callback).Run(true);
}

void OnGetCommandFinished(base::OnceCallback<void(bool)> callback, std::optional<ShellState> state) {
  if (!state || state->code != 0) {
    LOG(ERROR) << "Get dev mode " << " failed";
    std::move(callback).Run(false);
    return;
  }
  auto result = base::TrimWhitespaceASCII(state->result, base::TRIM_ALL);
  const bool enabled = result == "dev";
  std::move(callback).Run(enabled);
}

}  // namespace

bool IsDevModeSwitchSupported() {
  return base::PathExists(base::FilePath(bin_script));
}

void SetDevMode(const bool enabled, base::OnceCallback<void(bool)> callback) {
  Wings8OSShellClient* shellClient = GetShellClient();
  if (!shellClient) {
    std::move(callback).Run(false);
    return;
  }
  std::string command = base::StringPrintf("%s %s", bin_script, enabled ? enable_param : disable_param);
  shellClient->SyncExec(command,
      base::BindOnce(&OnSetCommandFinished, enabled, std::move(callback)));
}

void GetDevMode(base::OnceCallback<void(bool)> callback) {
  Wings8OSShellClient* shellClient = GetShellClient();
  if (!shellClient) {
    std::move(callback).Run(false);
    return;
  }
  std::string command = bin_script + std::string(" ") + query_param;
  shellClient->SyncExec(command,
      base::BindOnce(&OnGetCommandFinished, std::move(callback)));
}

} // namespace wings8os::misc

