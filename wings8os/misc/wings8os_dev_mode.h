// Copyright 2024 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_MISC_WINGS8OS_DEV_MODE_H_
#define WINGS8OS_MISC_WINGS8OS_DEV_MODE_H_

#include "base/functional/callback_forward.h"

namespace wings8os::misc {

bool IsDevModeSwitchSupported();
void SetDevMode(const bool enabled, base::OnceCallback<void(bool)> callback);
void GetDevMode(base::OnceCallback<void(bool)> callback);

}


#endif // !WINGS8OS_MISC_WINGS8OS_DEV_MODE_H_
