#include "chrome/browser/ash/system_web_apps/apps/wings8_assistant_app_info.h"

#include "ash/constants/ash_features.h"
#include "ash/webui/wings8_assistant_app_ui/url_constants.h"
#include "ash/webui/grit/ash_wings8_assistant_app_resources.h"
#include "chrome/browser/ash/system_web_apps/apps/system_web_app_install_utils.h"
#include "chrome/browser/web_applications/web_app_install_info.h"

#include <memory>

std::unique_ptr<web_app::WebAppInstallInfo> CreateWebAppInfoForWings8AssistantApp() {
  auto start_url = GURL(ash::kChromeUIWings8AssistantAppURL);
  auto info =
      web_app::CreateSystemWebAppInstallInfoWithStartUrlAsIdentity(start_url);
  info->scope = GURL(ash::kChromeUIWings8AssistantAppURL);
  info->title = u"Wings8OS AI";
  web_app::CreateIconInfoForSystemWebApp(
      info->start_url(),
      {{"app_icon_192.png", 192, IDR_ASH_WINGS8_ASSISTANT_APP_APP_ICON_192_PNG}},
      *info);
  info->display_mode = blink::mojom::DisplayMode::kStandalone;
  info->user_display_mode = web_app::mojom::UserDisplayMode::kStandalone;

  return info;
}

Wings8AssistantAppDelegate::Wings8AssistantAppDelegate(Profile* profile)
    : ash::SystemWebAppDelegate(ash::SystemWebAppType::WINGS8_ASSISTANT,
                                    "Wings8Assistant",
                                    GURL(ash::kChromeUIWings8AssistantAppURL),
                                    profile) {}

bool Wings8AssistantAppDelegate::ShouldCaptureNavigations() const  {
  return true;
}

std::unique_ptr<web_app::WebAppInstallInfo> Wings8AssistantAppDelegate::GetWebAppInfo() const {
  return CreateWebAppInfoForWings8AssistantApp();
}
bool Wings8AssistantAppDelegate::IsAppEnabled() const {
  return ash::features::IsWings8AssistantEnabled();
}

bool Wings8AssistantAppDelegate::ShouldShowInLauncher() const {
  // WINGS8OS: hide the Wings8OS AI app icon from the app launcher (the feature is
  // not ready yet). The app remains functional via its other entry points.
  return false;
}

bool Wings8AssistantAppDelegate::ShouldShowInSearchAndShelf() const {
  // WINGS8OS: also keep the Wings8OS AI icon out of search results and the shelf.
  return false;
}
