#include "wings8os/misc/wings8os_toggle_ota.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "base/logging.h"
#include "base/functional/bind.h"
#include "base/files/file_util.h"
#include "wings8os/chromeos/ash/components/dbus/wings8os_shell_client/wings8os_shell_client.h"

using wings8os::ash::Wings8OSShellClient;
using wings8os::ash::ShellState;

namespace wings8os {
namespace misc {

namespace {
  Wings8OSShellClient* GetShellClient() {
    return Wings8OSShellClient::Get();
  }

  const char kWings8OSOTAIndicatorFile[] = "/mnt/stateful_partition/unencrypted/preserve/.disable_wings8os_ota";

  std::string EnableOTACommand() {
    return std::string("rm ") + kWings8OSOTAIndicatorFile;
  }
  std::string DisableOTACommand() {
    return std::string("touch ") + kWings8OSOTAIndicatorFile;
  }

  void OnSetCommandFinished(const bool enabled, base::OnceCallback<void()> callback, absl::optional<ShellState> state) {
    if (!state || state->code != 0) {
      LOG(ERROR) << "Set Wings8OS OTA " << enabled << " failed";
    }
    std::move(callback).Run();
  }
}

void EnableWings8OTA(const bool enabled, base::OnceCallback<void()> callback) {
  Wings8OSShellClient* shellClient = GetShellClient();
  if (!shellClient) return;
  const std::string command = enabled ? EnableOTACommand() : DisableOTACommand();
  shellClient->SyncExec(command,
      base::BindOnce(&OnSetCommandFinished, enabled, std::move(callback)));
}

bool GetEnabledWings8OTA() {
  const bool enabled = !base::PathExists(base::FilePath(kWings8OSOTAIndicatorFile));
  return enabled;
}

} // misc
} // wings8os
