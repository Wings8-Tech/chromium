// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/misc/wings8os_misc_scheduler.h"
#include "wings8os/misc/wings8os_statistics_collector.h"
#include "wings8os/build/config/buildflags.h"
#include <base/logging.h>

#if BUILDFLAG(USE_WINGS8OS_COM)
#include "wings8os/misc/wings8os_crostini_notifier.h"
#endif

namespace wings8os {
namespace misc {

namespace {
  Wings8MiscScheduler* g_misc_scheduler = nullptr;
}

void Wings8MiscScheduler::Initialize() {
  CHECK(g_misc_scheduler == nullptr);
  g_misc_scheduler = new Wings8MiscScheduler();
}

Wings8MiscScheduler* Wings8MiscScheduler::Get() {
  return g_misc_scheduler;
}

void Wings8MiscScheduler::Shutdown() {
  CHECK(g_misc_scheduler != nullptr);
  g_misc_scheduler->Stop();
  delete g_misc_scheduler;
  g_misc_scheduler = nullptr;
}

Wings8MiscScheduler::Wings8MiscScheduler() :
#if BUILDFLAG(USE_WINGS8OS_COM)
  crostini_notifier_(std::make_unique<MiscCrostiniNotifier>()),
#endif
  collector_(std::make_unique<StatisticsCollector>()) {
  if (::ash::LoginState::IsInitialized()) {
    ::ash::LoginState::Get()->AddObserver(this);
  }
}

Wings8MiscScheduler::~Wings8MiscScheduler() = default;

void Wings8MiscScheduler::Start() {
  if (started_) return;
  VLOG(2) << "Wings8MiscScheduler Start";
  started_ = true;
  collector_->Start();
#if BUILDFLAG(USE_WINGS8OS_COM)
  crostini_notifier_->Start();
#endif
}

void Wings8MiscScheduler::Stop() {
  VLOG(2) << "Wings8MiscScheduler Stop";
  collector_->Stop();
  started_ = false;
}

void Wings8MiscScheduler::LoggedInStateChanged() {
  if (::ash::LoginState::Get()->IsUserLoggedIn() && ::ash::LoginState::Get()->IsUserAuthenticated()) {
    Start();
  } else {
    Stop();
  }
}

}  // namespace misc
}  // namespace wings8os
