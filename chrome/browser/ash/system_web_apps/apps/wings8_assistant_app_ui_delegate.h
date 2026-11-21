#ifndef CHROME_BROWSER_ASH_WEB_APPLICATIONS_WINGS8_ASSISTANT_APP_UI_DELEGATE_H_
#define CHROME_BROWSER_ASH_WEB_APPLICATIONS_WINGS8_ASSISTANT_APP_UI_DELEGATE_H_

#include "ash/webui/wings8_assistant_app_ui/wings8_assistant_app_ui_delegate.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"

namespace content {
class WebUI;
}

class ChromeWings8AssistantAppUIDelegate : public ash::Wings8AssistantAppUIDelegate {
 public:
  explicit ChromeWings8AssistantAppUIDelegate(content::WebUI* web_ui);

  ChromeWings8AssistantAppUIDelegate(const ChromeWings8AssistantAppUIDelegate&) = delete;
  ChromeWings8AssistantAppUIDelegate& operator=(const ChromeWings8AssistantAppUIDelegate&) = delete;
  ~ChromeWings8AssistantAppUIDelegate() override;

  // Wings8AssistantAppUIDelegate:
  void PopulateLoadTimeData(content::WebUIDataSource* source) override;

  ash::Wings8AssistantAppUIDelegate::ColorInfo GetSystemColorInfo() override;

 private:
  raw_ptr<content::WebUI> web_ui_;  // Owns |this|.
  base::WeakPtrFactory<ChromeWings8AssistantAppUIDelegate> weak_ptr_factory_{this};
};

#endif // !#ifndef CHROME_BROWSER_ASH_WEB_APPLICATIONS_WINGS8_ASSISTANT_APP_UI_DELEGATE_H_
