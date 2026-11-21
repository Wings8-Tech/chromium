// Copyright (c) 2021 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/ui/webui/settings/ash/wings8os_section.h"
#include "base/command_line.h"
#include "base/no_destructor.h"
#include "chrome/grit/generated_resources.h"
#include "chrome/grit/branded_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "content/public/browser/web_ui.h"
#include "chrome/browser/ui/webui/webui_util.h"
#include "ui/base/webui/web_ui_util.h"
#include "content/public/browser/web_ui_data_source.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "base/system/sys_info.h"
#include "chrome/browser/browser_process.h"
#include "wings8os/switches/misc/misc_switches.h"
#include "wings8os/switches/urls/urls_constants.h"

#include "base/strings/utf_string_conversions.h"

#include "wings8os/ui/webui/settings/ash/wings8os_handler.h"
#include "wings8os/prefs/wings8os_pref_names.h"
#include "wings8os/build/config/buildflags.h"

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
#include "wings8os/switches/license/license_switches.h"
#include "wings8os/license/wings8os_license_user_util.h"
#endif

#include "chromeos/dbus/constants/dbus_switches.h"

namespace ash::settings {

namespace mojom {
using ::chromeos::settings::mojom::kWings8OsSectionPath;
using ::chromeos::settings::mojom::kWings8OsSubpagePath;
#if BUILDFLAG(USE_WINGS8OS_LICENSE)
using ::chromeos::settings::mojom::kWings8OsLicenseInfoSubpagePath;
#endif
using ::chromeos::settings::mojom::Section;
using ::chromeos::settings::mojom::Subpage;
using ::chromeos::settings::mojom::Setting;
}

namespace {
  const std::vector<SearchConcept>& GetWings8OsSearchConcepts() {
    static const base::NoDestructor<std::vector<SearchConcept>> tags({
      {IDS_OS_SETTINGS_WINGS8OS_SETTINGS,
       mojom::kWings8OsSubpagePath,
       mojom::SearchResultIcon::kChrome,
       mojom::SearchResultDefaultRank::kMedium,
       mojom::SearchResultType::kSubpage,
       {.subpage = mojom::Subpage::kWings8OsMain}},
#if BUILDFLAG(USE_WINGS8OS_LICENSE)
      {IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_TITLE,
       mojom::kWings8OsLicenseInfoSubpagePath,
       mojom::SearchResultIcon::kChrome,
       mojom::SearchResultDefaultRank::kMedium,
       mojom::SearchResultType::kSubpage,
       {.subpage = mojom::Subpage::kWings8OsLicenseInfo}},
#endif
    });
    return *tags;
  }

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
  const char kWings8OSLicenseLookupPath[] = "/web/license.html";
#endif
}  // namespace

Wings8OsSection::Wings8OsSection(Profile* profile,
                           SearchTagRegistry* search_tag_registry,
                           PrefService* pref_service)
  : OsSettingsSection(profile, search_tag_registry),
    pref_service_(pref_service) {
  SearchTagRegistry::ScopedTagUpdater updater = registry()->StartUpdate();
  updater.AddSearchTags(GetWings8OsSearchConcepts());
}

Wings8OsSection::~Wings8OsSection() = default;

void Wings8OsSection::AddLoadTimeData(content::WebUIDataSource* html_source) {
  static constexpr webui::LocalizedString kLocalizedStrings[] = {
    {"wings8osSettingsAccountTitle", IDS_OS_SETTINGS_WINGS8OS_ACCOUNT_TITLE},
    {"wings8osSettingsRemoteAssistanceTitle",
      IDS_OS_SETTINGS_WINGS8OS_REMOTE_ASSISTANCE_TITLE},
    {"wings8osSettingsRemoteHelperServiceTitle",
      IDS_OS_SETTINGS_WINGS8OS_REMOTE_HELPER_SERVICE_TITLE},
    {"wings8osSettingsRemoteHelperDesc",
      IDS_OS_SETTINGS_WINGS8OS_REMOTE_HELPER_SERVICE_DESC},
    {"wings8osSettingsRemoteHelperEnabledMessage",
      IDS_OS_SETTINGS_WINGS8OS_REMOTE_HELPER_SERVICE_ENABLED_MESSAGE},
    {"wings8osSettingsRemoteHelperRequireRestartMessage",
      IDS_OS_SETTINGS_WINGS8OS_REMOTE_HELPER_SERVICE_REQUIRE_RESTART_MESSAGE},
    {"wings8osSettingsRemoteHelperStartingMessage",
      IDS_OS_SETTINGS_WINGS8OS_REMOTE_HELPER_SERVICE_STARGING_MESSAGE},
    {"wings8osSettingsMoreInfoTitle", IDS_OS_SETTINGS_WINGS8OS_MORE_INFO_TITLE},

    {"wings8osSettingsOtherTweaksTitle",
      IDS_OS_SETTINGS_WINGS8OS_OTHER_TWEAKS_TITLE},
    {"rebootButtonInTrayLabel",
      IDS_OS_SETTINGS_WINGS8OS_REBOOT_BUTTON_IN_TRAY_LABEL},
    {"displayWings8OsRebootButtonInTray",
      IDS_OS_SETTINGS_WINGS8OS_DISPLAY_REBOOT_BUTTON_IN_TRAY},
    {"rotateScreenButtonInTrayLabel",
      IDS_OS_SETTINGS_WINGS8OS_ROTATE_SCREEN_BUTTON_IN_TRAY_LABEL},
    {"notTabletPhysicalStateDisableWings8OsRotateScreen",
      IDS_OS_SETTINGS_WINGS8OS_NOT_TABLET_STATE_DISABLE_ROTATE_SCREEN},
    {"displayWings8OsRotateScreenButton",
      IDS_OS_SETTINGS_WINGS8OS_DISPLAY_ROTATE_SCREEN_BUTTON},
    {"switchTabletLaptopModeButtonInTrayLabel",
      IDS_OS_SETTINGS_WINGS8OS_SWITCH_TABLET_LAPTOP_MODE_BUTTON_IN_TRAY_LABEL},
    {"displaySwitchTabletLaptopModeButton",
      IDS_OS_SETTINGS_WINGS8OS_DISPLAY_SWITCH_TABLET_LAPTOP_MODE_BUTTON},
    {"enableLibwidevineLabel", IDS_OS_SETTINGS_WINGS8OS_ENABLE_LIBWIDEVINE_LABEL},
    {"failedEnableWidevineTitle",
      IDS_OS_SETTINGS_WINGS8OS_FAILED_ENABLE_WIDEVINE_TITLE},
    {"failedEnableWidevineMessage",
      IDS_OS_SETTINGS_WINGS8OS_FAILED_ENABLE_WIDEVINE_MESSAGE},
    {"wings8osCpuTurboLabel", IDS_OS_SETTINGS_WINGS8OS_CPU_TURBO_LABEL},
    {"wings8osCpuTurboHelpMessage", IDS_OS_SETTINGS_WINGS8OS_CPU_TURBO_HELP_MESSAGE},
    {"wings8osCpuTurboFailedTitle", IDS_OS_SETTINGS_WINGS8OS_FAILED_CPU_TURBO_TITLE},
    {"wings8osCpuTurboFailedMessage", IDS_OS_SETTINGS_WINGS8OS_FAILED_CPU_TURBO_MESSAGE},
    {"wings8osSettingsMenuItemDescription",
      IDS_OS_SETTINGS_WINGS8OS_MENU_ITEM_DESCRIPTION},
    {"wings8osExperimentalFeatures",
      IDS_OS_SETTINGS_WINGS8OS_EXPERIMENTAL_FEATURES_TITLE},
    {"wings8osBypassTpmChecksTitle",
      IDS_OS_SETTINGS_WINGS8OS_BYPASS_TPM_CHECKS_TITLE},
    {"wings8osBypassTpmChecksDesc",
      IDS_OS_SETTINGS_WINGS8OS_BYPASS_TPM_CHECKS_DESC},

    {"autoSigninForWings8LocalAccountTitle",
      IDS_OS_SETTINGS_WINGS8OS_AUTO_SIGNIN_FOR_LOCAL_ACCOUNT_TITLE},
    {"enableAutoSigninForWings8LocalAccountHelpMessage",
      IDS_OS_SETTINGS_WINGS8OS_ENABLE_AUTO_SIGNIN_FOR_LOCAL_ACCOUNT_MESSAGE},
    {"autoSigninForWings8LocalAccountOtherUserAlreadyEnabled",
      IDS_OS_SETTINGS_WINGS8OS_AUTO_SIGNIN_FOR_LOCAL_ACCOUNT_ALREADY_ENABLED_BY_OTHER},
    {"unableToSetAutoSigninForWings8LocalAccount",
      IDS_OS_SETTINGS_WINGS8OS_UNABLE_TO_SET_AUTO_SIGNIN_FOR_LOCAL_ACCOUNT},
    {"unableToSetAutoSigninForWings8NonLocalAccount",
      IDS_OS_SETTINGS_WINGS8OS_UNABLE_TO_SET_AUTO_SIGNIN_FOR_NON_LOCAL_ACCOUNT},
    {"unableToSetAutoSigninWithoutPasswordAuthFactor",
      IDS_OS_SETTINGS_WINGS8OS_UNABLE_TO_SET_AUTO_SIGNIN_WITHOUT_PASSWORD_AUTH_FACTOR},

    {"wings8osSettingsBackupSaveFileDialogTitle",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_SAVE_FILE_DIALOG_TITLE},
    {"wings8osSettingsBackupButtonLabel",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_BUTTON_LABEL},
    {"wings8osSettingsBackupIntroTitle",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_INTRO_TITLE},
    {"wings8osSettingsBackupPasswordPromptTitle",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_PASSWORD_PROMPT_TITLE},
    {"wings8osSettingsBackupPasswordPromptText",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_PASSWORD_PROMPT_TEXT},

    {"wings8osSettingsRestoreSelectFileDialogTitle",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_SELECT_FILE_DIALOG_TITLE},
    {"wings8osSettingsRestoreLabel",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_LABEL},
    {"wings8osSettingsRestoreButtonLabel",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_BUTTON_LABEL},
    {"wings8osSettingsRestorePasswordDialogTitle",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_PASSWORD_DIALOG_TITLE},
    {"wings8osSettingsRestorePasswordDialogMessage",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_PASSWORD_DIALOG_MESSAGE},
    {"wings8osSettingsRestorePasswordLabel",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_PASSWORD_LABEL},
    {"wings8osSettingsRestorePasswordError",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_PASSWORD_ERROR},
    {"wings8osSettingsRestoreSuccessTitle",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_SUCCESS_TITLE},
    {"wings8osSettingsRestoreErrorTitle",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_ERROR_TITLE},

    // Cloud backup/restore strings
    {"wings8osSettingsBackupLocalDesc",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_LOCAL_DESC},
    {"wings8osSettingsCloudBackupLabel",
      IDS_OS_SETTINGS_WINGS8OS_CLOUD_BACKUP_LABEL},
    {"wings8osSettingsCloudBackupDesc",
      IDS_OS_SETTINGS_WINGS8OS_CLOUD_BACKUP_DESC},
    {"wings8osSettingsCloudBackupButtonLabel",
      IDS_OS_SETTINGS_WINGS8OS_CLOUD_BACKUP_BUTTON_LABEL},
    {"wings8osSettingsRestoreLocalDesc",
      IDS_OS_SETTINGS_WINGS8OS_RESTORE_LOCAL_DESC},
    {"wings8osSettingsCloudRestoreLabel",
      IDS_OS_SETTINGS_WINGS8OS_CLOUD_RESTORE_LABEL},
    {"wings8osSettingsCloudRestoreDesc",
      IDS_OS_SETTINGS_WINGS8OS_CLOUD_RESTORE_DESC},
    {"wings8osSettingsCloudRestoreButtonLabel",
      IDS_OS_SETTINGS_WINGS8OS_CLOUD_RESTORE_BUTTON_LABEL},

    // Backup API and Storage strings
    {"wings8osSettingsConnectApiUserInfoTitle",
      IDS_OS_SETTINGS_WINGS8OS_CONNECT_API_USER_INFO_TITLE},
    {"wings8osSettingsLoading",
      IDS_OS_SETTINGS_WINGS8OS_LOADING},
    {"wings8osSettingsUserIdLabel",
      IDS_OS_SETTINGS_WINGS8OS_USER_ID_LABEL},
    {"wings8osSettingsStatusLabel",
      IDS_OS_SETTINGS_WINGS8OS_STATUS_LABEL},
    {"wings8osSettingsBackupStorageAnalysisTitle",
      IDS_OS_SETTINGS_WINGS8OS_BACKUP_STORAGE_ANALYSIS_TITLE},
    {"wings8osSettingsUserIdRequired",
      IDS_OS_SETTINGS_WINGS8OS_USER_ID_REQUIRED},
    {"wings8osSettingsStorageLabel",
      IDS_OS_SETTINGS_WINGS8OS_STORAGE_LABEL},
    {"wings8osSettingsLastUpdatedLabel",
      IDS_OS_SETTINGS_WINGS8OS_LAST_UPDATED_LABEL},
    {"wings8osSettingsHardwareDevicesLabel",
      IDS_OS_SETTINGS_WINGS8OS_HARDWARE_DEVICES_LABEL},
    {"wings8osSettingsNoBackupData",
      IDS_OS_SETTINGS_WINGS8OS_NO_BACKUP_DATA},
    {"wings8osSettingsUnavailable",
      IDS_OS_SETTINGS_WINGS8OS_UNAVAILABLE},

    // Restore dialog strings
    {"wings8osSettingsClose",
      IDS_OS_SETTINGS_WINGS8OS_CLOSE},
    {"wings8osSettingsLoadingBackupFiles",
      IDS_OS_SETTINGS_WINGS8OS_LOADING_BACKUP_FILES},
    {"wings8osSettingsSelectBackupFileLabel",
      IDS_OS_SETTINGS_WINGS8OS_SELECT_BACKUP_FILE_LABEL},
    {"wings8osSettingsSelectBackupFilePlaceholder",
      IDS_OS_SETTINGS_WINGS8OS_SELECT_BACKUP_FILE_PLACEHOLDER},
    {"wings8osSettingsNoBackupFilesFound",
      IDS_OS_SETTINGS_WINGS8OS_NO_BACKUP_FILES_FOUND},

    // Wings8OS AI Assistant strings
    {"wings8osComingSoon",
      IDS_OS_SETTINGS_WINGS8OS_COMING_SOON},

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
    {"wings8osSettingsLicenseStateLoading",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_STATE_LOADING},
    {"wings8osSettingsLicenseRetryButtonText",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_RETRY_BUTTON},
    {"wings8osSettingsLicenseLabel",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_MENU},
    {"wings8osSettingsLicenseTitle",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_TITLE},
    {"wings8osSettingsLicenseErrorReadMachineId",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_ERROR_MACHINE_ID},
    {"wings8osSettingsLicenseIdLabel",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_ID_LABEL},
    {"wings8osSettingsLicenseExpireDateLabel",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_EXPIRE_DATE_LABEL},
    {"wings8osSettingsLicenseRetryWebviewButtonText",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_RETRY_WEBVIEW_BUTTON},
    {"wings8osSettingsLicenseOfflineHintMessage",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_OFFLINE_HINT_MESSAGE},
#endif
    {"wings8osSettingsSecuritySectionTitle",
      IDS_OS_SETTINGS_WINGS8OS_SECURITY_SECTION_TITLE},
    {"wings8osSettingsEnableDevModeButtonText",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_ENABLE_DEV_MODE_BUTTON_TEXT},
    {"wings8osSettingsInDevModeTooltip",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_IN_DEV_MODE_TOOLTIP},
    {"wings8osSettingsEnableDevModeConfirmTitle",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_ENABLE_DEV_MODE_CONFIRM_TITLE},
    {"wings8osSettingsEnableDevModeConfirmMessage",
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_ENABLE_DEV_MODE_CONFIRM_MESSAGE},
  };

  html_source->AddLocalizedStrings(kLocalizedStrings);
  html_source->AddString("wings8osSettingsPageTitle",
      l10n_util::GetStringFUTF16(IDS_OS_SETTINGS_WINGS8OS_SETTINGS,
        l10n_util::GetStringUTF16(IDS_PRODUCT_OS_NAME)));

  html_source->AddString(
      "wings8osSettingsBackupLabel",
      l10n_util::GetStringFUTF16(IDS_OS_SETTINGS_WINGS8OS_BACKUP_LABEL,
          base::ASCIIToUTF16(
            wings8os::constants::kWings8OSBackupRestoreLearnMoreURL)));
  html_source->AddString(
      "wings8osSettingsBackupIntroText",
      l10n_util::GetStringFUTF16(
          IDS_OS_SETTINGS_WINGS8OS_BACKUP_INTRO_TEXT,
          base::ASCIIToUTF16(
            wings8os::constants::kWings8OSBackupRestoreLearnMoreURL)));

  html_source->AddString(
      "toggleWidevineHelpMessage",
      l10n_util::GetStringFUTF16(
          IDS_OS_SETTINGS_WINGS8OS_TOGGLE_LIBWIDEVINE_HELP_MESSAGE,
            base::ASCIIToUTF16(
              wings8os::constants::kWings8OSEnableWidevineLearnMoreURL)));

  html_source->AddString(
      "toggleArcMediaAutoScanLabel",
      l10n_util::GetStringFUTF16(
          IDS_OS_SETTINGS_WINGS8OS_TOGGLE_ARC_MEDIA_AUTO_SCAN_LABEL,
            base::ASCIIToUTF16(
              wings8os::constants::kWings8OSToggleArcMediaAutoScanLearnMoreURL)));

  html_source->AddString(
      "wings8osSettingsDevModeTransitionLabel",
      l10n_util::GetStringFUTF16(IDS_OS_SETTINGS_WINGS8OS_DEV_MODE_TRANSITION_LABEL,
                                 l10n_util::GetStringUTF16(IDS_PRODUCT_OS_NAME),
                                 base::ASCIIToUTF16(
                                 wings8os::constants::kWings8OSDevModeTransitionLearnMoreURL)));

  const std::string board = base::SysInfo::GetLsbReleaseBoard();
  html_source->AddBoolean("showToggleRebootButtonInTray", false);
  html_source->AddBoolean("showToggleRotateScreenButton",
      wings8os::switches::IsNonForYouBoard(board));
  html_source->AddBoolean("showToggleSwitchTabletLaptopButton", true);

  html_source->AddString("wings8OSRdpUrl",
      wings8os::constants::kWings8OSRemoteDesktopURL);
  html_source->AddString("wings8osAccountBaseUrl",
      wings8os::constants::kWings8OSAccountBaseUrl);

  html_source->AddBoolean("isTpmFallbackNecessary",
      g_browser_process->local_state()->GetBoolean(
        wings8os::prefs::kForceTpmFallbackNecessary));
  html_source->AddString("wings8ExperimentTpmfallbackUrl",
      wings8os::constants::kWings8ExperimentTpmFallbackUrl);

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
  html_source->AddBoolean("showWings8OsLicense", g_browser_process->local_state()->GetBoolean(wings8os::prefs::kWings8LicenseShouldShowInSettings));

  GURL url(wings8os::switches::GetWings8OSLicenseWebUrl() + kWings8OSLicenseLookupPath);
  html_source->AddString("wings8osSettingsLicenseUrl",
      wings8os::license::AppendAccountIdQueryParameter(url).spec());
  html_source->AddString("wings8osBoardName", board);
#endif

  html_source->AddBoolean("devMode",
                          base::CommandLine::ForCurrentProcess()->HasSwitch(
                          chromeos::switches::kSystemDevMode));
}

int Wings8OsSection::GetSectionNameMessageId() const {
  return IDS_OS_SETTINGS_WINGS8OS_SETTINGS;
}

mojom::Section Wings8OsSection::GetSection() const {
  return mojom::Section::kWings8Os;
}

mojom::SearchResultIcon Wings8OsSection::GetSectionIcon() const {
  NOTIMPLEMENTED();
  return mojom::SearchResultIcon::kChrome;
}

const char* Wings8OsSection::GetSectionPath() const {
  return mojom::kWings8OsSectionPath;
}

void Wings8OsSection::AddHandlers(content::WebUI* web_ui) {
  web_ui->AddMessageHandler(
      std::make_unique<Wings8OsHandler>(profile(), pref_service_));
}

bool Wings8OsSection::LogMetric(
    mojom::Setting setting, base::Value& value) const {
  // Unimplemented.
  return false;
}

void Wings8OsSection::RegisterHierarchy(HierarchyGenerator* generator) const {
  // wings8os top level
  generator->RegisterTopLevelSubpage(
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS, mojom::Subpage::kWings8OsMain,
      mojom::SearchResultIcon::kChrome, mojom::SearchResultDefaultRank::kMedium,
      mojom::kWings8OsSubpagePath);

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
  // license info.
  generator->RegisterNestedSubpage(
      IDS_OS_SETTINGS_WINGS8OS_SETTINGS_WINGS8OS_LICENSE_INFO_TITLE,
      mojom::Subpage::kWings8OsLicenseInfo, mojom::Subpage::kWings8OsMain,
      mojom::SearchResultIcon::kChrome, mojom::SearchResultDefaultRank::kMedium,
      mojom::kWings8OsLicenseInfoSubpagePath);
#endif
}

}  // namespace ash::settings
