#ifndef ASH_WEBUI_WINGS8_ASSISTANT_APP_UI_WINGS8_ASSISTANT_APP_WEBUI_HANDLER_H_
#define ASH_WEBUI_WINGS8_ASSISTANT_APP_UI_WINGS8_ASSISTANT_APP_WEBUI_HANDLER_H_

#include "content/public/browser/web_ui_message_handler.h"
#include "ash/webui/wings8_assistant_app_ui/wings8_assistant_app_ui.h"
#include "ash/public/cpp/assistant/controller/assistant_controller.h"
#include "ash/public/cpp/assistant/controller/assistant_controller_observer.h"
#include "ash/assistant/model/assistant_ui_model_observer.h"
#include "ui/native_theme/native_theme.h"
#include "ui/native_theme/native_theme_observer.h"
#include "ash/wings8os_ai/wings8os_ai_view.h"
#include "services/network/public/cpp/network_connection_tracker.h"

namespace ash {

class Wings8AssistantWebUIHandler
    : public content::WebUIMessageHandler,
      public network::NetworkConnectionTracker::NetworkConnectionObserver,
      public ui::NativeThemeObserver,
      public AssistantUiModelObserver,
      public Wings8AssistantViewObserver,
      public AssistantControllerObserver {

 public:
  explicit Wings8AssistantWebUIHandler(Wings8AssistantAppUI* wings8AsisstantAppUi);

  Wings8AssistantWebUIHandler(const Wings8AssistantWebUIHandler&) = delete;
  Wings8AssistantWebUIHandler& operator=(const Wings8AssistantWebUIHandler&) =
      delete;

  ~Wings8AssistantWebUIHandler() override;

  // content::WebUIMessageHandler:
  void RegisterMessages() override;

  // ash::AssistantUiModelObserver:
  void OnUiVisibilityChanged(
      AssistantVisibility new_visibility,
      AssistantVisibility old_visibility,
      std::optional<AssistantEntryPoint> entry_point,
      std::optional<AssistantExitPoint> exit_point) override;

  // AssistantControllerObserver:
  void OnDeepLinkReceived(
      assistant::util::DeepLinkType type,
      const std::map<std::string, std::string>& params) override;

  // ui::NativeThemeObserver:
  void OnNativeThemeUpdated(ui::NativeTheme* observed_theme) override;

  // network::NetworkConnectionTracker::NetworkConnectionObserver:
  void OnConnectionChanged(network::mojom::ConnectionType type) override;

  void OnBubbleQueryChanged(const Wings8AssistantViewObserver::ClipboardItemForAssistant& item) override;
  void OnBubbleVisibilityChanged(bool visible) override;
 private:
  void OnWings8AssistantSwaInit(const base::Value::List& args);
  void OnRequestCloseAssistant(const base::Value::List& args);

  void OnWings8AssistantOpenUrl(const base::Value::List& args);
  void HandleSetAssistantBubbleRect(const base::Value::List& args);
  void HandleCenterAssistantBubbleRect(const base::Value::List& args);

  raw_ptr<Wings8AssistantAppUI> wings8_assistant_app_ui_;

  base::ScopedObservation<AssistantController, AssistantControllerObserver>
      assistant_controller_observation_{this};

  base::ScopedObservation<ui::NativeTheme, ui::NativeThemeObserver>
      theme_observation_{this};
};

} // namespace ash

#endif // !#ifndef ASH_WEBUI_WINGS8_ASSISTANT_APP_UI_WINGS8_ASSISTANT_APP_WEBUI_HANDLER_H_
