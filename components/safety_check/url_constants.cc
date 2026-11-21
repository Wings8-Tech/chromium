// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/safety_check/url_constants.h"
#include "wings8os/build/config/buildflags.h"

namespace safety_check {

#if BUILDFLAG(USE_WINGS8OS_COM)
const char kConnectivityCheckUrl[] =
    "https://store.wings8.org/204";
#else
const char kConnectivityCheckUrl[] =
    "https://connectivitycheck.gstatic.com/generate_204";
#endif

}  // namespace safety_check
