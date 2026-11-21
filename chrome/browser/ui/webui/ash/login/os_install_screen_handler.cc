// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/webui/ash/login/os_install_screen_handler.h"

#include <string>

#include "base/notreached.h"
#include "base/time/time.h"
#include "chrome/browser/ash/login/screens/os_install_screen.h"
#include "chrome/grit/branded_strings.h"
#include "chrome/grit/generated_resources.h"
#include "components/login/localized_values_builder.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/l10n/time_format.h"
#include "ui/strings/grit/ui_strings.h"
#include "components/user_manager/user_manager.h"
#include "base/system/sys_info.h"

namespace ash {
namespace {
constexpr const char kInProgressStep[] = "in-progress";
constexpr const char kFailedStep[] = "failed";
constexpr const char kNoDestinationDeviceFoundStep[] =
    "no-destination-device-found";
constexpr const char kSuccessStep[] = "success";
}  // namespace

OsInstallScreenHandler::OsInstallScreenHandler()
    : BaseScreenHandler(kScreenId) {}

OsInstallScreenHandler::~OsInstallScreenHandler() = default;

void OsInstallScreenHandler::DeclareLocalizedValues(
    ::login::LocalizedValuesBuilder* builder) {
  builder->AddF("osInstallDialogIntroTitle", IDS_OS_INSTALL_SCREEN_INTRO_TITLE,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("osInstallDialogIntroSubtitle",
                IDS_OS_INSTALL_SCREEN_INTRO_SUBTITLE,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("osInstallDialogIntroBody0",
                IDS_OS_INSTALL_SCREEN_INTRO_CONTENT_0,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("osInstallDialogIntroBody1",
               IDS_OS_INSTALL_SCREEN_INTRO_CONTENT_1);
  builder->AddF("osInstallDialogIntroFooter",
                IDS_OS_INSTALL_SCREEN_INTRO_FOOTER,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("osInstallDialogIntroNextButton",
                IDS_OS_INSTALL_SCREEN_INTRO_NEXT_BUTTON,
                IDS_INSTALLED_PRODUCT_OS_NAME);

  builder->AddF("osInstallDialogConfirmTitle",
                IDS_OS_INSTALL_SCREEN_CONFIRM_TITLE,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("osInstallDialogConfirmBody",
               IDS_OS_INSTALL_SCREEN_CONFIRM_BODY);
  builder->Add("osInstallDialogConfirmNextButton",
               IDS_OS_INSTALL_SCREEN_CONFIRM_NEXT_BUTTON);

  builder->AddF("osInstallDialogInProgressTitle",
                IDS_OS_INSTALL_SCREEN_IN_PROGRESS_TITLE,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("osInstallDialogInProgressSubtitle",
               IDS_OS_INSTALL_SCREEN_IN_PROGRESS_SUBTITLE);

  builder->Add("osInstallDialogErrorTitle", IDS_OS_INSTALL_SCREEN_ERROR_TITLE);
  builder->AddF("osInstallDialogErrorFailedSubtitle",
                IDS_OS_INSTALL_SCREEN_ERROR_FAILED_SUBTITLE,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("osInstallDialogErrorNoDestSubtitle",
                IDS_OS_INSTALL_SCREEN_ERROR_NO_DEST_SUBTITLE,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("osInstallDialogErrorNoDestContent",
               IDS_OS_INSTALL_SCREEN_ERROR_NO_DEST_CONTENT);
  builder->Add("osInstallDialogServiceLogsTitle",
               IDS_OS_INSTALL_SCREEN_SERVICE_LOGS_TITLE);
  builder->Add("osInstallDialogErrorViewLogs",
               IDS_OS_INSTALL_SCREEN_ERROR_VIEW_LOGS);

  builder->Add("osInstallDialogSuccessTitle",
               IDS_OS_INSTALL_SCREEN_SUCCESS_TITLE);

  builder->Add("osInstallDialogSendFeedback",
               IDS_OS_INSTALL_SCREEN_SEND_FEEDBACK);
  builder->Add("osInstallDialogShutdownButton",
               IDS_OS_INSTALL_SCREEN_SHUTDOWN_BUTTON);

  DeclareWings8InstallerLocalizedValues(builder);
}

void OsInstallScreenHandler::GetAdditionalParameters(base::Value::Dict* parameters) {
  if (user_manager::UserManager::Get()->IsUserLoggedIn())
    return;
  parameters->Set("lsbReleaseBoard", base::SysInfo::GetLsbReleaseBoardWithoutSuffix());
}

void OsInstallScreenHandler::DeclareWings8InstallerLocalizedValues(
    ::login::LocalizedValuesBuilder* builder) {
  builder->Add("wings8osInstallerAppName", IDS_WINGS8OS_INSTALLER_APP_NAME);
  builder->AddF("wings8osInstallerAppDesc", IDS_WINGS8OS_INSTALLER_APP_DESC,
                IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerAppDisclaimer",
               IDS_WINGS8OS_INSTALLER_APP_DISCLAIMER);
  builder->Add("wings8osInstallerFullDiskInstallationTitle",
               IDS_WINGS8OS_INSTALLER_FULL_DISK_INSTALLATION_TITLE);
  builder->AddF("wings8osInstallerFullDiskInstallationHelperText",
               IDS_WINGS8OS_INSTALLER_FULL_DISK_INSTALLATION_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerDualbootInstallationTitle",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_INSTALLATION_TITLE);
  builder->AddF("wings8osInstallerDualbootInstallationHelperText",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_INSTALLATION_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerFullDiskInstallationDisclaimer",
               IDS_WINGS8OS_INSTALLER_FULL_DISK_INSTALLATION_DISCLAIMER,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerDualbootInstallationDesc",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_INSTALLATION_DESC,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerDualbootInstallationDisclaimer",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_INSTALLATION_DISCLAIMER);
  builder->Add("wings8osInstallerInstallButton",
               IDS_WINGS8OS_INSTALLER_TEXT_ON_INSTALL_BUTTON);
  builder->Add("wings8osInstallerConfigDiskSelectLabel",
               IDS_WINGS8OS_INSTALLER_CONFIG_DISK_SELECT_LABEL);
  builder->Add("wings8osInstallerNormalConfigNoAvailableDisk",
               IDS_WINGS8OS_INSTALLER_NORMAL_CONFIG_NO_AVAILABLE_DISK);
  builder->Add("wings8osInstallerInstalling",
               IDS_WINGS8OS_INSTALLER_INSTALLING_TITLE);
  builder->Add("wings8osInstallerShutdownButton",
               IDS_WINGS8OS_INSTALLER_TEXT_ON_SHUTDOWN_BUTTON);
  builder->Add("wings8osInstallerInstallSuccessTitle",
               IDS_WINGS8OS_INSTALLER_INSTALL_SUCCESS_TITLE);
  builder->Add("wings8osInstallerInstallFailedTitle",
               IDS_WINGS8OS_INSTALLER_INSTALL_FAILED_TITLE);
  builder->AddF("wings8osInstallerInstallSuccessMessage",
               IDS_WINGS8OS_INSTALLER_INSTALL_SUCCESS_MESSAGE,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerInstallFailedMessage",
               IDS_WINGS8OS_INSTALLER_INSTALL_FAILED_MESSAGE);
  builder->AddF("wings8osInstallDualbootConfigSelectOSPart",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_CONFIG_SELECT_OS_PARTITION,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerDualbootConfigPartSelectLabel",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_CONFIG_PARTITION_SELECT_LABEL);
  builder->Add("wings8osInstallDualbootConfigSelectEFIPart",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_CONFIG_SELECT_EFI_PARTITION);
  builder->Add("wings8osInstallerDualbootSelectedDiskHasNoAvailOSPart",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_SELECTED_DISK_HAS_NO_AVAIL_OS_PARTITION);
  builder->Add("wings8osInstallerDualbootSelectedDiskHasNoAvailEFIPart",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_SELECTED_DISK_HAS_NO_AVAIL_EFI_PARTITION);
  builder->Add("wings8osInstallerDualbootSelectedOSPartSizeSmaller",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_SELECTED_PARTITION_SIZE_SMALLER);
  builder->AddF("wings8osInstallerDualbootSelectedOSPartAlreadyInstalled",
               IDS_WINGS8OS_INSTALLER_DUALBOOT_SELECTED_PARTITION_ALREADY_INSTALLED,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerMultiBootOptionTitle",
               IDS_WINGS8OS_INSTALLER_MULTI_BOOT_OPTION_TITLE,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerInstallREFIndTitle",
               IDS_WINGS8OS_INSTALLER_INSTALL_REFIND_TITLE);
  builder->Add("wings8osInstallerInstallREFIndHelperText",
               IDS_WINGS8OS_INSTALLER_INSTALL_REFIND_HELPER_TEXT);
  builder->Add("wings8osInstallerInstallUefiBootTitle",
               IDS_WINGS8OS_INSTALLER_INSTALL_UEFI_BOOT_TITLE);
  builder->AddF("wings8osInstallerInstallUefiBootHelperText",
               IDS_WINGS8OS_INSTALLER_INSTALL_UEFI_BOOT_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerMultiBootConfigureByYourselfTitle",
               IDS_WINGS8OS_INSTALLER_MULTI_BOOT_CONFIGURE_BY_YOURSELF_TITLE);
  builder->AddF("wings8osInstallerMultiBootConfigureByYourselfHelperText",
               IDS_WINGS8OS_INSTALLER_MULTI_BOOT_CONFIGURE_BY_YOURSELF_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerAbortButton",
               IDS_WINGS8OS_INSTALLER_TEXT_ON_ABORT_BUTTON);
  builder->Add("wings8osInstallerAbortTitle",
               IDS_WINGS8OS_INSTALLER_ABORT_TITLE);
  builder->Add("wings8osInstallerAbortMessage",
               IDS_WINGS8OS_INSTALLER_ABORT_MESSAGE);
  builder->Add("wings8osInstallerGetDiskInfoFailed",
               IDS_WINGS8OS_INSTALLER_GET_DISK_INFO_FAILED);
  builder->Add("wings8osInstallerAbortingMessage",
               IDS_WINGS8OS_INSTALLER_ABORTING_MESAGE);
  builder->Add("wings8osInstallerUsbInstallationTitle",
               IDS_WINGS8OS_INSTALLER_USB_INSTALLATION_TITLE);
  builder->AddF("wings8osInstallerUsbInstallationHelperText",
               IDS_WINGS8OS_INSTALLER_USB_INSTALLATION_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerUsbInstallationDisclaimer",
               IDS_WINGS8OS_INSTALLER_USB_INSTALLATION_DISCLAIMER,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerUsbConfigNoAvailableDisk",
               IDS_WINGS8OS_INSTALLER_USB_CONFIG_NO_AVAILABLE_DISK);
  builder->AddF("wings8osInstallerCreateOSPartOption",
               IDS_WINGS8OS_INSTALLER_CREATE_OS_PART_OPTION,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerCreateOSPartSizeLabel",
               IDS_WINGS8OS_INSTALLER_CREATE_OS_PART_SIZE_LABEL,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerCreateOSPartSizeHelperText",
               IDS_WINGS8OS_INSTALLER_CREATE_OS_PART_SIZE_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerShrinkOSPartOption",
               IDS_WINGS8OS_INSTALLER_SHRINK_OS_PART_OPTION,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->AddF("wings8osInstallerShrinkOSPartHelperText",
               IDS_WINGS8OS_INSTALLER_SHRINK_OS_PART_HELPER_TEXT,
               IDS_INSTALLED_PRODUCT_OS_NAME);
  builder->Add("wings8osInstallerCreateOSPartFailed",
               IDS_WINGS8OS_INSTALLER_CREATE_OS_PART_FAILED);

  builder->Add("wings8osOobeWelcomeDisableNextDesc",
               IDS_WINGS8OS_OOBE_WELCOME_DISABLE_NEXT_DESC);
  builder->Add("wings8osOobeWelcomeDisableNextContinueAnyway",
               IDS_WINGS8OS_OOBE_WELCOME_DISABLE_NEXT_CONTINUE_ANYWAY);
}

void OsInstallScreenHandler::Show() {
  ShowInWebUI();
}

void OsInstallScreenHandler::ShowStep(const char* step) {
  CallExternalAPI("showStep", std::string(step));
}

void OsInstallScreenHandler::SetStatus(OsInstallClient::Status status) {
  switch (status) {
    case OsInstallClient::Status::InProgress:
      ShowStep(kInProgressStep);
      break;
    case OsInstallClient::Status::Succeeded:
      ShowStep(kSuccessStep);
      break;
    case OsInstallClient::Status::Failed:
      ShowStep(kFailedStep);
      break;
    case OsInstallClient::Status::NoDestinationDeviceFound:
      ShowStep(kNoDestinationDeviceFoundStep);
      break;
  }
}

void OsInstallScreenHandler::SetServiceLogs(const std::string& service_log) {
  CallExternalAPI("setServiceLogs", service_log);
}

void OsInstallScreenHandler::UpdateCountdownStringWithTime(
    base::TimeDelta time_left) {
  CallExternalAPI(
      "updateCountdownString",
      l10n_util::GetStringFUTF8(
          IDS_OS_INSTALL_SCREEN_SUCCESS_SUBTITLE,
          ui::TimeFormat::Simple(ui::TimeFormat::FORMAT_DURATION,
                                 ui::TimeFormat::LENGTH_LONG, time_left),
          l10n_util::GetStringUTF16(IDS_INSTALLED_PRODUCT_OS_NAME)));
}

base::WeakPtr<OsInstallScreenView> OsInstallScreenHandler::AsWeakPtr() {
  return weak_factory_.GetWeakPtr();
}

}  // namespace ash
