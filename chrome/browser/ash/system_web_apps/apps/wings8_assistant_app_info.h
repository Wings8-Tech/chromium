#ifndef CHROME_BROWSER_ASH_WEB_APPLICATIONS_WINGS8_ASSISTANT_APP_INFO_H_
#define CHROME_BROWSER_ASH_WEB_APPLICATIONS_WINGS8_ASSISTANT_APP_INFO_H_


#include "chrome/browser/ash/system_web_apps/types/system_web_app_delegate.h"

namespace web_app {
struct WebAppInstallInfo;
}  // namespace web_app

class Wings8AssistantAppDelegate : public ash::SystemWebAppDelegate {
  public:
    explicit Wings8AssistantAppDelegate(Profile* profile);

  // ash::SystemWebAppDelegate overrides:
  std::unique_ptr<web_app::WebAppInstallInfo> GetWebAppInfo() const override;
  bool ShouldCaptureNavigations() const override;
  bool IsAppEnabled() const override;
  bool ShouldShowInLauncher() const override;
  bool ShouldShowInSearchAndShelf() const override;
  // NOTE: there are more virtual methods in the base class.
};

// Return a WebAppInstallInfo used to install the app.
std::unique_ptr<web_app::WebAppInstallInfo> CreateWebAppInfoForWings8AssistantApp();

#endif  // WINGS8OS_CHROME_BROWSER_ASH_WEB_APPLICATIONS_START_ARC_SETTINGS_WEB_APP_INFO_H_
