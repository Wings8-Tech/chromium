// Copyright 2024 The Wings8 Technology Limited. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "wings8os/ui/webui/settings/ash/wings8_assistant_section.h"

#include "ash/constants/ash_features.h"
#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "wings8os/switches/misc/misc_switches.h"

namespace ash::settings {

namespace mojom {
using ::chromeos::settings::mojom::kWings8AssistantSectionPath;
using ::chromeos::settings::mojom::Section;
using ::chromeos::settings::mojom::Subpage;
using ::chromeos::settings::mojom::Setting;
} // namespace mojom

namespace {
  const std::vector<SearchConcept>& GetWings8AssistantSearchConcepts() {
    static const base::NoDestructor<std::vector<SearchConcept>> tags({
      {IDS_OS_SETTINGS_WINGS8_ASSISTANT,
       mojom::kWings8AssistantSectionPath,
       mojom::SearchResultIcon::kAssistant,
       mojom::SearchResultDefaultRank::kMedium,
       mojom::SearchResultType::kSetting,
       {.setting = mojom::Setting::kWings8AssistantSettings}},
    });
    return *tags;
  }
}

Wings8AssistantSection::Wings8AssistantSection(Profile* profile,
                                           SearchTagRegistry* search_tag_registry,
                                           PrefService* pref_service)
  : OsSettingsSection(profile, search_tag_registry),
    pref_service_(pref_service) {
  SearchTagRegistry::ScopedTagUpdater updater = registry()->StartUpdate();
  updater.AddSearchTags(GetWings8AssistantSearchConcepts());
}

Wings8AssistantSection::~Wings8AssistantSection() = default;

void Wings8AssistantSection::AddLoadTimeData(content::WebUIDataSource* html_source) {
  static constexpr webui::LocalizedString kLocalizedStrings[] = {
    {"wings8AssistantPageTitle", IDS_OS_SETTINGS_WINGS8_ASSISTANT},
    {"wings8AssistantMenuItemDescription", IDS_OS_SETTINGS_WINGS8_ASSISTANT_MENU_ITEM_DESCRIPTION},
    {"wings8AssistantToggleLabel", IDS_OS_SETTINGS_WINGS8_ASSISTANT_TOGGLE_LABEL},
    {"wings8AssistantToggleSublabel", IDS_OS_SETTINGS_WINGS8_ASSISTANT_TOGGLE_SUBLABEL},
    {"wings8AssistantBubbleShortcutToggleLabel", IDS_OS_SETTINGS_WINGS8_ASSISTANT_BUBBLE_SHORTCUT_TOGGLE_LABEL},
    {"wings8AssistantBubbleShortcutToggleSublabel", IDS_OS_SETTINGS_WINGS8_ASSISTANT_BUBBLE_SHORTCUT_TOGGLE_SUBLABEL},
    {"wings8AssistantSettingsInAppLabel", IDS_OS_SETTINGS_WINGS8_ASSISTANT_SETTINGS_IN_APP_LABEL},
    {"wings8AssistantSettingsInAppSublabel", IDS_OS_SETTINGS_WINGS8_ASSISTANT_SETTINGS_IN_APP_SUBLABEL},
  };
  html_source->AddLocalizedStrings(kLocalizedStrings);
  html_source->AddBoolean("wings8AssistantFeatureEnabled",ash::features::IsWings8AssistantEnabled());
  html_source->AddBoolean("isWings8AiHidden", wings8os::switches::IsWings8AiHidden());
}

void Wings8AssistantSection::AddHandlers(content::WebUI* web_ui) {

}

int Wings8AssistantSection::GetSectionNameMessageId() const {
  return IDS_OS_SETTINGS_WINGS8_ASSISTANT;
}
chromeos::settings::mojom::Section Wings8AssistantSection::GetSection() const {
  return mojom::Section::kWings8Assistant;
}

ash::settings::mojom::SearchResultIcon Wings8AssistantSection::GetSectionIcon() const {
  return mojom::SearchResultIcon::kAssistant;
}

const char* Wings8AssistantSection::GetSectionPath() const {
  return mojom::kWings8AssistantSectionPath;
}

bool Wings8AssistantSection::LogMetric(chromeos::settings::mojom::Setting setting,
               base::Value& value) const {
  return false;
}

void Wings8AssistantSection::RegisterHierarchy(HierarchyGenerator* generator) const {
  generator->RegisterTopLevelSetting(mojom::Setting::kWings8AssistantSettings);
}

} // namespace ash::settings
