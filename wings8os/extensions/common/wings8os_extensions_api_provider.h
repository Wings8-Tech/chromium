// Copyright 2018 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINGS8OS_EXTENSIONS_API_PROVIDER_H_
#define WINGS8OS_EXTENSIONS_API_PROVIDER_H_

#include "wings8os/extensions/common/wings8os_api_permissions.h"
#include "extensions/common/extensions_api_provider.h"

namespace extensions {

class Wings8OSExtensionsAPIProvider : public ExtensionsAPIProvider {
 public:
  Wings8OSExtensionsAPIProvider();
  ~Wings8OSExtensionsAPIProvider() override;

  // ExtensionsAPIProvider:
  void AddAPIFeatures(FeatureProvider* provider) override;
  void AddManifestFeatures(FeatureProvider* provider) override;
  void AddPermissionFeatures(FeatureProvider* provider) override;
  void AddBehaviorFeatures(FeatureProvider* provider) override;
  void AddAPIJSONSources(JSONFeatureProviderSource* json_source) override;
  bool IsAPISchemaGenerated(const std::string& name) override;
  std::string_view GetAPISchema(const std::string& name) override;
  void RegisterPermissions(PermissionsInfo* permissions_info) override;
  void RegisterManifestHandlers() override;
};

}  // namespace extensions

#endif  // WINGS8OS_EXTENSIONS_API_PROVIDER_H_
