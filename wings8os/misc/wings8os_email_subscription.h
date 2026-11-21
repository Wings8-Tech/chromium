// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_EMAIL_SUBSCRIPTION_H
#define WINGS8OS_EMAIL_SUBSCRIPTION_H

class Profile;

namespace wings8os {

namespace misc {

void Subscribe(Profile* profile, bool email_opt_in, bool improve_plan_opt_in);

} // misc

} // wings8os


#endif
