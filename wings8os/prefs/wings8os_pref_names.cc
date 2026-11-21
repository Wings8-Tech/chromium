// Copyright (c) 2021 The Wings8OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wings8os/prefs/wings8os_pref_names.h"

namespace wings8os {
namespace prefs {

const char kPrefHideWings8OSStoreIcon[] = "hide_wings8os_store_icon";

const char kWings8OSImprovementPlanEnabled[] = "wings8os_improvement_plan_enabled";

// local state
const char kEnableArcIMEGlobally[] = "enable_arc_ime_globally";
const char kCurrentEnableArcIMEGlobally[] = "current_enable_arc_ime_globally";

const char kForceTpmFallbackNecessary[] = "force_tpm_fallback_necessary";
const char kCurrentForceTpmFallback[] = "current_force_tpm_fallback";
const char kForceTpmFallback[] = "force_tpm_fallback";

const char kShowSwitchTabletLaptopButton[] = "show_switch_tablet_laptop_button";
const char kShowRebootButtonInTray[] = "show_reboot_button_in_tray";
const char kShowRotateScreenButton[] = "show_rotate_screen_button";

const char kOfflineAutoSigninAccountIdKey[] =
    "offline_auto_signin.account_id_key";
const char kOfflineAutoSigninPassword[] = "offline_auto_signin.password";
const char kOfflineAutoSigninPasswordFormat[] =
    "offline_auto_signin.password_format";
const char kOfflineAutoSigninIsChromeLastSignout[] =
    "offline_auto_signin.chrome_signout";

const char kConnectApiUserId[] = "connect_api.user_id";
// UID materiel genere en dernier recours par GetDeviceUid (aucune source
// d identite native : PC generique sans VPD ni machine-id).
const char kWings8OsDeviceUid[] = "wings8os.device_uid";
const char kConnectApiUserStatus[] = "connect_api.user_status";

const char kWings8SubscriptionActive[] = "wings8os.subscription_active";
const char kWings8SeatDeactivated[] = "wings8os.seat_deactivated";

const char kFactoryResetRequested[] = "FactoryResetRequested";

const char kRebootRequiredForWidevine[] = "reboot_required_for_widevine";

const char kCpuTurboEnabled[] = "wings8os_cpu_turbo_enabled";

const char kWings8AssistantEnabled[] = "wings8_assistant_enabled";
const char kWings8AssistantExtraAcceleratorEnabled[] =
    "wings8_assistant_extra_accelerator_enabled";

const char kWings8OsAuthAccessTokenEncrypted[] =
    "wings8os_auth.access_token_encrypted";
const char kWings8OsAuthRefreshTokenEncrypted[] =
    "wings8os_auth.refresh_token_encrypted";
const char kWings8OsAuthEmail[] = "wings8os_auth.email";
const char kWings8OsAuthIssuedAt[] = "wings8os_auth.issued_at";
const char kWings8OsAuthPasswordVersion[] = "wings8os_auth.password_version";
const char kWings8OsSavedPasswords[] = "wings8os_auth.saved_passwords";
const char kWings8OsVaultSecrets[] = "wings8os_auth.vault_secrets";

const char kWings8OSArcMediaAutoScanEnabled[] =
    "wings8os_arc_media_auto_scan_enabled";

#if BUILDFLAG(USE_WINGS8OS_LICENSE)
const char kWings8LicenseShouldShowInSettings[] =
    "wings8_license_should_show_in_settings";
const char kWings8LicenseStateType[] = "wings8_license_state_type";
const char kWings8LicenseEnforcementLevel[] = "wings8_license_enforcement_level";
const char kWings8LicenseEnforcementLogOutInterval[] =
    "wings8o_license_enforcement_log_out_interval";
#endif

#if BUILDFLAG(USE_WINGS8OS_COM)
const char kCrostiniInstallerNotificationUserInteracted[] =
    "wings8os_crostini_installer_notificaion_user_interacted";
#endif
}  // namespace prefs
}  // namespace wings8os
