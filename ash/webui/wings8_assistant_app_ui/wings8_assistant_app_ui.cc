#include "ash/webui/wings8_assistant_app_ui/wings8_assistant_app_ui.h"

#include "ash/webui/wings8_assistant_app_ui/url_constants.h"
#include "chrome/browser/ash/system_web_apps/apps/system_web_app_install_utils.h"
#include "ash/webui/grit/ash_wings8_assistant_app_resources.h"
#include "ash/webui/grit/ash_wings8_assistant_app_resources_map.h"

#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_contents.h"

#include "ash/bubble/bubble_constants.h"

#include "content/public/browser/web_ui_message_handler.h"
#include "ash/webui/wings8_assistant_app_ui/wings8_assistant_app_webui_handler.h"
#include "wings8os/switches/services/services_switches.h"
#include "ash/public/cpp/assistant/assistant_state.h"

namespace ash {

Wings8AssistantAppUI::Wings8AssistantAppUI(content::WebUI* web_ui,
                                      std::unique_ptr<Wings8AssistantAppUIDelegate> delegate)
  : content::WebUIController(web_ui), delegate_(std::move(delegate)) {
  auto* browser_context = web_ui->GetWebContents()->GetBrowserContext();
  content::WebUIDataSource* html_source =
      content::WebUIDataSource::CreateAndAdd(browser_context,
                                             kChromeUIWings8AssistantAppHost);
  html_source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ScriptSrc,
      "script-src chrome://resources chrome://test chrome://webui-test "
      "'self';");
  html_source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::WorkerSrc,
    "worker-src blob: chrome://resources 'self';");
  html_source->DisableTrustedTypesCSP();
  html_source->AddResourcePath("", IDR_ASH_WINGS8_ASSISTANT_APP_INDEX_HTML);
  html_source->AddResourcePaths(base::make_span(
      kAshWings8AssistantAppResources, kAshWings8AssistantAppResourcesSize));

  html_source->SetDefaultResource(IDR_ASH_WINGS8_ASSISTANT_APP_INDEX_HTML);

  html_source->AddInteger("borderRadiusInLauncher", kBubbleCornerRadius);
  html_source->AddInteger("borderRadiusInBubble", kBubbleCornerRadiusForAI);
  html_source->AddString("wings8osAssistantUrl", wings8os::switches::GetWings8OSAssistantWebUrl());
  html_source->AddBoolean("isWings8OSAssistantEnabled", ash::AssistantState::Get()->wings8_assistant_enabled().value_or(false));
  html_source->UseStringsJs();

  delegate_->PopulateLoadTimeData(html_source);

  web_ui->AddMessageHandler(std::make_unique<Wings8AssistantWebUIHandler>(this));
}

Wings8AssistantAppUI::~Wings8AssistantAppUI() = default;

WEB_UI_CONTROLLER_TYPE_IMPL(Wings8AssistantAppUI)

} // namespace ash
