// Copyright 2023 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef WINGS8OS_EXTENSIONS_BROWSER_API_WINGS8OS_PRIVATE_WINGS8OS_PRIVATE_API_H_
#define WINGS8OS_EXTENSIONS_BROWSER_API_WINGS8OS_PRIVATE_WINGS8OS_PRIVATE_API_H_

#include "extensions/browser/extension_function.h"
#include "extensions/browser/extension_function_histogram_value.h"

namespace extensions {
class Wings8osPrivateGetWings8OSInfoFunction: public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("wings8osPrivate.getWings8OSInfo",
                              WINGS8OS_PRIVATE_GET_WINGS8OS_INFO)

 protected:
  ~Wings8osPrivateGetWings8OSInfoFunction() override = default;
  ResponseAction Run() override;
};
}  // namespace extensions


#endif  // WINGS8OS_EXTENSIONS_BROWSER_API_WINGS8OS_PRIVATE_WINGS8OS_PRIVATE_API_H_
