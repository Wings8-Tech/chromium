// Copyright (c) 2019 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/switches/arc/arc_switches.h"
#include "base/command_line.h"
#include <string>

namespace wings8os {
namespace switches {

namespace {

const char kWings8OSArcDelay[] ="wings8os-arc-delay";

}

int64_t GetWings8OSArcDelay() {
	std::string delayStr = base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(kWings8OSArcDelay);
	if (delayStr.empty())
		return 0;
	return (int64_t) std::stoi(delayStr);
}

} // switches
} // wings8os

