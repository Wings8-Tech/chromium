// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/extensions/common/wings8os_extensions_api_provider.h"

#include "wings8os/extensions/common/api/api_features.h"
#include "wings8os/extensions/common/api/generated_schemas.h"
#include "wings8os/extensions/common/api/permission_features.h"
#include "wings8os/extensions/common/wings8os_api_permissions.h"
#include "wings8os/extensions/common/grit/wings8os_extensions_resources.h"
#include "extensions/common/features/json_feature_provider_source.h"
#include "extensions/common/permissions/permissions_info.h"
#include "base/logging.h"

namespace extensions {

Wings8OSExtensionsAPIProvider::Wings8OSExtensionsAPIProvider() {}
Wings8OSExtensionsAPIProvider::~Wings8OSExtensionsAPIProvider() = default;

void Wings8OSExtensionsAPIProvider::AddAPIFeatures(FeatureProvider* provider) {
  AddWings8OSAPIFeatures(provider);
  VLOG(1) << "Add wings8os api features\n";
}

void Wings8OSExtensionsAPIProvider::AddManifestFeatures(
    FeatureProvider* provider) {
}

void Wings8OSExtensionsAPIProvider::AddPermissionFeatures(
    FeatureProvider* provider) {
  AddWings8OSPermissionFeatures(provider);
  VLOG(1) << "Add wings8os permission features\n";
}

void Wings8OSExtensionsAPIProvider::AddBehaviorFeatures(
    FeatureProvider* provider) {
  // Note: No chrome-specific behavior features.
}

void Wings8OSExtensionsAPIProvider::AddAPIJSONSources(
    JSONFeatureProviderSource* json_source) {
  json_source->LoadJSON(IDR_WINGS8OS_EXTENSION_API_FEATURES);
}

bool Wings8OSExtensionsAPIProvider::IsAPISchemaGenerated(
    const std::string& name) {
  return api::Wings8OSGeneratedSchemas::IsGenerated(name);
}

std::string_view Wings8OSExtensionsAPIProvider::GetAPISchema(
    const std::string& name) {
  return api::Wings8OSGeneratedSchemas::Get(name);
}

void Wings8OSExtensionsAPIProvider::RegisterPermissions(PermissionsInfo* permissions_info) {
  permissions_info->RegisterPermissions(
      wings8os_api_permissions::GetPermissionInfos(),
      wings8os_api_permissions::GetPermissionAliases());
  VLOG(1) << "register wings8os permissions";
}

void Wings8OSExtensionsAPIProvider::RegisterManifestHandlers() {
}

}  // namespace extensions
