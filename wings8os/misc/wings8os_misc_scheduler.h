// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_MISC_SCHEDULER_H_
#define WINGS8OS_MISC_SCHEDULER_H_

#include <memory>
#include "chromeos/chromeos_export.h"
#include "chromeos/ash/components/login/login_state/login_state.h"
#include "wings8os/build/config/buildflags.h"

namespace wings8os {
namespace misc {

class StatisticsCollector;
class MiscCrostiniNotifier;

class CHROMEOS_EXPORT Wings8MiscScheduler : public ::ash::LoginState::Observer {
 public:
    Wings8MiscScheduler();
    ~Wings8MiscScheduler() override;
    static void Initialize();
    static Wings8MiscScheduler* Get();
    static void Shutdown();
    void Start();
    void Stop();

 private:
    void LoggedInStateChanged() override;

    bool started_ = false;
#if BUILDFLAG(USE_WINGS8OS_COM)
    std::unique_ptr<MiscCrostiniNotifier> crostini_notifier_;
#endif
    std::unique_ptr<StatisticsCollector> collector_;
};

}  // namespace misc
}  // namespace wings8os

#endif /* ifndef WINGS8OS_MISC_SCHEDULER_H_ */
