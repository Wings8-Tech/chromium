#ifndef ASH_WEBUI_WINGS8_ASSISTANT_APP_UI_WINGS8_ASSISTANT_APP_UI_H_
#define ASH_WEBUI_WINGS8_ASSISTANT_APP_UI_WINGS8_ASSISTANT_APP_UI_H_

#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_controller.h"
#include "ash/webui/wings8_assistant_app_ui/url_constants.h"
#include "ash/webui/system_apps/public/system_web_app_type.h"
#include "ash/webui/system_apps/public/system_web_app_ui_config.h"
#include "ash/webui/wings8_assistant_app_ui/wings8_assistant_app_ui_delegate.h"

namespace ash {

class Wings8AssistantAppUI;
class Wings8AssistantAppUIConfig : public SystemWebAppUIConfig<Wings8AssistantAppUI> {
 public:
  explicit Wings8AssistantAppUIConfig(
      SystemWebAppUIConfig::CreateWebUIControllerFunc create_controller_func)
      : SystemWebAppUIConfig(ash::kChromeUIWings8AssistantAppHost,
                             SystemWebAppType::WINGS8_ASSISTANT,
                             create_controller_func) {}
};

class Wings8AssistantAppUI : public content::WebUIController {
 public:
  explicit Wings8AssistantAppUI(content::WebUI* web_ui,
                              std::unique_ptr<Wings8AssistantAppUIDelegate> delegate);
  Wings8AssistantAppUI(const Wings8AssistantAppUI&) = delete;
  Wings8AssistantAppUI& operator=(const Wings8AssistantAppUI&) = delete;
  ~Wings8AssistantAppUI() override;

  Wings8AssistantAppUIDelegate* delegate() { return delegate_.get(); }

private:
  std::unique_ptr<Wings8AssistantAppUIDelegate> delegate_;
  WEB_UI_CONTROLLER_TYPE_DECL();
};

} // namespace ash


#endif  // WINGS8OS_ASH_WEBUI_WINGS8_ASSISTANT_APP_UI_WINGS8_ASSISTANT_APP_UI_H_
