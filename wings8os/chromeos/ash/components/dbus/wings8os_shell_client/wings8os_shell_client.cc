// Copyright (c) 2018 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/chromeos/ash/components/dbus/wings8os_shell_client/wings8os_shell_client.h"

#include <stdint.h>

#include <utility>

#include "base/functional/bind.h"
#include "base/logging.h"
#include "base/format_macros.h"
#include "base/strings/stringprintf.h"
#include "dbus/bus.h"
#include "dbus/message.h"
#include "dbus/object_path.h"
#include "dbus/object_proxy.h"

namespace wings8os {
namespace ash {

namespace {

const char kWings8OSShellServiceName[] = "io.wings8os.ShellDaemon";
const char kWings8OSShellServicePath[] = "/io/wings8os/ShellDaemon";
const char kWings8OSShellServiceInterface[] = "io.wings8os.ShellInterface";
const char kShellSyncExec[] = "SyncExec";
const char kShellAsyncExec[] = "AsyncExec";
const char kShellGetTaskOutput[] = "GetAsyncTaskOutput";
const char kShellGetTaskState[] = "GetTaskState";
const char kShellForceCloseTask[] = "ForceCloseTask";
const char kShellGetDaemonState[] = "GetDaemonState";
const char kShellSystemNotify[] = "ShellNotifying";
enum NotificationType { SYSTEM, COMMAND };

Wings8OSShellClient* g_instance = nullptr;

class Wings8OSShellClientImpl : public Wings8OSShellClient {
  public:
    Wings8OSShellClientImpl() : shell_proxy_(nullptr) {}
    Wings8OSShellClientImpl& operator=(const Wings8OSShellClientImpl&) = delete;

    ~Wings8OSShellClientImpl() override = default;

    void SyncExec(const std::string& cmd, chromeos::DBusMethodCallback<ShellState> callback) override {
      SyncExecWithTimeout(cmd, dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
                          std::move(callback));
    }

    void SyncExecWithTimeout(const std::string& cmd, int timeout_ms, chromeos::DBusMethodCallback<ShellState> callback) override {
      VLOG(1) << "SyncExec received command:" << cmd;
      dbus::MethodCall method_call(kWings8OSShellServiceInterface, kShellSyncExec);
      dbus::MessageWriter writer(&method_call);
      writer.AppendString(cmd);
      shell_proxy_->CallMethod(&method_call,
          timeout_ms,
          base::BindOnce(&Wings8OSShellClientImpl::OnShellDaemonReturn,
            weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
    }

    void AsyncExec(const std::string& cmd, chromeos::DBusMethodCallback<ShellState> callback) override {
      VLOG(1) << "AsyncExec reveived command:" << cmd;
      dbus::MethodCall method_call(kWings8OSShellServiceInterface, kShellAsyncExec);
      dbus::MessageWriter writer(&method_call);
      writer.AppendString(cmd);
      shell_proxy_->CallMethod(&method_call,
                      dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
                      base::BindOnce(&Wings8OSShellClientImpl::OnShellDaemonReturn,
                              weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
    }

    void GetTaskOutput(int32_t key, int32_t lines, chromeos::DBusMethodCallback<ShellState> callback) override {
      dbus::MethodCall method_call(kWings8OSShellServiceInterface, kShellGetTaskOutput);
      dbus::MessageWriter writer(&method_call);
      writer.AppendInt32(key);
      writer.AppendInt32(lines);
      shell_proxy_->CallMethod(&method_call,
                      dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
                      base::BindOnce(&Wings8OSShellClientImpl::OnShellDaemonReturn,
                              weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
    }

    void GetTaskState(int32_t key, chromeos::DBusMethodCallback<ShellState> callback) override {
      dbus::MethodCall method_call(kWings8OSShellServiceInterface, kShellGetTaskState);
      dbus::MessageWriter writer(&method_call);
      writer.AppendInt32(key);
      shell_proxy_->CallMethod(&method_call,
                      dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
                      base::BindOnce(&Wings8OSShellClientImpl::OnShellDaemonReturn,
                              weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
    }

    void ForceCloseTask(int32_t key, chromeos::DBusMethodCallback<ShellState> callback) override {
      dbus::MethodCall method_call(kWings8OSShellServiceInterface, kShellForceCloseTask);
      dbus::MessageWriter writer(&method_call);
      writer.AppendInt32(key);
      shell_proxy_->CallMethod(&method_call,
                      dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
                      base::BindOnce(&Wings8OSShellClientImpl::OnShellDaemonReturn,
                              weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
    }

    void GetDaemonState(chromeos::DBusMethodCallback<ShellState> callback) override {
      dbus::MethodCall method_call(kWings8OSShellServiceInterface, kShellGetDaemonState);
      shell_proxy_->CallMethod(&method_call,
                      dbus::ObjectProxy::TIMEOUT_USE_DEFAULT,
                      base::BindOnce(&Wings8OSShellClientImpl::OnShellDaemonReturn,
                              weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
    }

    void AddObserver(Observer* observer) override {
      observers_.AddObserver(observer);
    }

    void RemoveObserver(Observer* observer) override {
      observers_.RemoveObserver(observer);
    }

    bool HasObserver(const Observer* observer) const override {
      return observers_.HasObserver(observer);
    }

    void Init(dbus::Bus* bus) override {
      shell_proxy_ = bus->GetObjectProxy(kWings8OSShellServiceName,
          dbus::ObjectPath(kWings8OSShellServicePath));
      shell_proxy_->ConnectToSignal(
        kWings8OSShellServiceInterface, kShellSystemNotify,
        base::BindRepeating(&Wings8OSShellClientImpl::OnShellSignalReceived,
          weak_ptr_factory_.GetWeakPtr()),
        base::BindOnce(&Wings8OSShellClientImpl::SignalConnected,
          weak_ptr_factory_.GetWeakPtr())
      );
      VLOG(1) << "Init shell_proxy";
    }

  private:
    void SignalConnected(const std::string& interface_name,
                      const std::string& signal_name,
                      bool success) {
      if (!success)
        LOG(ERROR) << "Failed to connect to signal " <<  signal_name << ".";
      else
        VLOG(1) << "Success to connnect to signal " << signal_name;
    }

    void OnShellSignalReceived(dbus::Signal* signal) {
      int32_t type, handler, state;
      std::string msg;
      dbus::MessageReader reader(signal);
      if (!reader.PopInt32(&type) ||
          !reader.PopInt32(&handler) ||
          !reader.PopInt32(&state) ||
          !reader.PopString(&msg)) {
        LOG(ERROR) << "Error reading signal: " << signal->ToString();
        return;
      }
      VLOG(1) << "Get notify type:" << type << " handler:" << handler
        << " state:" << state << " msg:" << msg;
      switch (type) {
        case NotificationType::SYSTEM:
          for (auto& observer : observers_)
            observer.OnSystemNotificationReceived(state, std::move(msg));
          break;
        case NotificationType::COMMAND:
          for (auto& observer : observers_)
            observer.OnCommandNotificationReceived(handler, state, std::move(msg));
          break;
        default:
          for (auto& observer : observers_)
            observer.OnCustomNotificationReceived(handler, state, std::move(msg));
          break;
      }
    }

    void OnShellDaemonReturn(chromeos::DBusMethodCallback<ShellState> callback,
        dbus::Response* response) {
      if (!response) {
        LOG(ERROR) << "Error calling Wings8OS shell daemon";
        std::move(callback).Run(std::nullopt);
        return;
      }
      ShellState shell_state;
      dbus::MessageReader reader(response);
      dbus::MessageReader sub_reader(nullptr);
      if (!reader.PopStruct(&sub_reader) ||!sub_reader.PopInt32(&shell_state.code) ||
          !sub_reader.PopString(&shell_state.result)) {
        LOG(ERROR) << "Error reading response from Wings8OS shell daemon: "
                << response->ToString();
        std::move(callback).Run(std::nullopt);
        return;
      }
      VLOG(1) << "Return code:" << shell_state.code;
      std::move(callback).Run(std::move(shell_state));
    }

    dbus::ObjectProxy* shell_proxy_;
    base::ObserverList<Observer>::Unchecked observers_;
    base::WeakPtrFactory<Wings8OSShellClientImpl> weak_ptr_factory_{this};
};// Wings8OSShellClientImpl

} // namespace

// static
Wings8OSShellClient* Wings8OSShellClient::Get() {
  return g_instance;
}

// static
void Wings8OSShellClient::Initialize(dbus::Bus* bus) {
  CHECK(bus);
  (new Wings8OSShellClientImpl())->Init(bus);
}

// static
void Wings8OSShellClient::Shutdown() {
  CHECK(g_instance);
  delete g_instance;
}

Wings8OSShellClient::Wings8OSShellClient() {
  CHECK(!g_instance);
  g_instance = this;
}

Wings8OSShellClient::~Wings8OSShellClient() {
  CHECK_EQ(g_instance, this);
  g_instance = nullptr;
}

} // namespace ash
} // namespace wings8os
