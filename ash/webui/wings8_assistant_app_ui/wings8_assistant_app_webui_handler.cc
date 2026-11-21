#include "ash/webui/wings8_assistant_app_ui/wings8_assistant_app_webui_handler.h"
#include "ash/public/cpp/new_window_delegate.h"
#include "ash/public/cpp/assistant/controller/assistant_ui_controller.h"
#include "ash/app_list/app_list_controller_impl.h"
#include "ash/assistant/util/deep_link_util.h"
#include "ash/assistant/model/assistant_ui_model.h"
#include "ash/shell.h"
#include "chrome/browser/ash/system_web_apps/color_helpers.h"
#include "content/public/browser/network_service_instance.h"
#include "ui/color/color_provider_utils.h"

namespace ash {

Wings8AssistantWebUIHandler::Wings8AssistantWebUIHandler(Wings8AssistantAppUI* app_ui):wings8_assistant_app_ui_(app_ui) {
  assistant_controller_observation_.Observe(AssistantController::Get());
  theme_observation_.Observe(ui::NativeTheme::GetInstanceForNativeUi());
  AssistantUiController::Get()->GetModel()->AddObserver(this);
  content::GetNetworkConnectionTracker()->AddNetworkConnectionObserver(this);
  Shelf* shelf = Shelf::ForWindow(Shell::GetPrimaryRootWindow());
  if  (shelf && shelf->wings8_assistant_view()) {
    shelf->wings8_assistant_view()->AddObserver(this);
  }
}

Wings8AssistantWebUIHandler::~Wings8AssistantWebUIHandler() {
  if (AssistantUiController::Get())
    AssistantUiController::Get()->GetModel()->RemoveObserver(this);
  content::GetNetworkConnectionTracker()->RemoveNetworkConnectionObserver(this);
  Shelf* shelf = Shelf::ForWindow(Shell::GetPrimaryRootWindow());
  if  (shelf && shelf->wings8_assistant_view()) {
    shelf->wings8_assistant_view()->RemoveObserver(this);
  }
}

void Wings8AssistantWebUIHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "onWings8AssistantSwaInit",
      base::BindRepeating(&Wings8AssistantWebUIHandler::OnWings8AssistantSwaInit,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "onCloseAssistant",
      base::BindRepeating(&Wings8AssistantWebUIHandler::OnRequestCloseAssistant,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "onOpenAssistantUrl",
      base::BindRepeating(&Wings8AssistantWebUIHandler::OnWings8AssistantOpenUrl,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setAssistantBubbleRect",
      base::BindRepeating(&Wings8AssistantWebUIHandler::HandleSetAssistantBubbleRect,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "centerAssistantBubble",
      base::BindRepeating(&Wings8AssistantWebUIHandler::HandleCenterAssistantBubbleRect,
                          base::Unretained(this)));
}

void Wings8AssistantWebUIHandler::OnWings8AssistantSwaInit(const base::Value::List& args) {
  AllowJavascript();
}

void Wings8AssistantWebUIHandler::OnRequestCloseAssistant(const base::Value::List& args) {
  CHECK_EQ(1u, args.size());
  const std::string source = args[0].GetString();
  if (source == "launcher") {
    auto* const app_list_controller = Shell::Get()->app_list_controller();
    if (app_list_controller) {
      app_list_controller->CloseWings8Assistant();
    }
    return;
  }

  if (source == "bubble") {
    Shelf* shelf = Shelf::ForWindow(Shell::GetPrimaryRootWindow());
    if  (shelf && shelf->wings8_assistant_view()) {
      shelf->wings8_assistant_view()->HideBubble();
    }
  }
}

void Wings8AssistantWebUIHandler::OnWings8AssistantOpenUrl(const base::Value::List& args) {
  CHECK_EQ(1u, args.size());
  const std::string url = args[0].GetString();
  VLOG(3) << "OnWings8AssistantOpenUrl, url: " << url;
  ash::NewWindowDelegate::GetPrimary()->OpenUrl(
    GURL(url), ash::NewWindowDelegate::OpenUrlFrom::kUserInteraction,
    ash::NewWindowDelegate::Disposition::kNewWindow);
}

void Wings8AssistantWebUIHandler::HandleSetAssistantBubbleRect(const base::Value::List& args) {
  CHECK_EQ(4u, args.size());
  const int x = args[0].GetInt();
  const int y = args[1].GetInt();
  const int width = args[2].GetInt();
  const int height = args[3].GetInt();
  VLOG(3) << "HandleSetAssistantBubbleRect: " << x << ", " << y << ", " << width << ", " << height;
  Shelf* shelf = Shelf::ForWindow(Shell::GetPrimaryRootWindow());
  if  (shelf && shelf->wings8_assistant_view()) {
    shelf->wings8_assistant_view()->SetBubbleRect(x, y, width, height);
  }
}

void Wings8AssistantWebUIHandler::HandleCenterAssistantBubbleRect(const base::Value::List& args) {
  CHECK_EQ(2u, args.size());
  const int width = args[0].GetInt();
  const int height = args[1].GetInt();
  VLOG(3) << "HandleCenterAssistantBubbleRect: " << width << ", " << height;
  Shelf* shelf = Shelf::ForWindow(Shell::GetPrimaryRootWindow());
  if  (shelf && shelf->wings8_assistant_view()) {
    shelf->wings8_assistant_view()->CenterBubble(width, height);
  }
}

void Wings8AssistantWebUIHandler::OnDeepLinkReceived(
    assistant::util::DeepLinkType type,
    const std::map<std::string, std::string>& params) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  if (type == assistant::util::DeepLinkType::kQuery) {
    const std::optional<std::string>& query =
      GetDeepLinkParam(params, assistant::util::DeepLinkParam::kQuery);
    if (query.has_value() && IsJavascriptAllowed()) {
      FireWebUIListener("query-from-launcher", base::Value(query.value()));
    }
  }
}

void Wings8AssistantWebUIHandler::OnUiVisibilityChanged(
      AssistantVisibility new_visibility,
      AssistantVisibility old_visibility,
      std::optional<AssistantEntryPoint> entry_point,
      std::optional<AssistantExitPoint> exit_point) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  if (new_visibility == AssistantVisibility::kVisible || new_visibility == AssistantVisibility::kClosed) {
    base::Value::Dict value;
    value.Set("visible", new_visibility == AssistantVisibility::kVisible);
    value.Set("entry", static_cast<int>(entry_point.has_value() ? entry_point.value() : AssistantEntryPoint::kUnspecified));
    FireWebUIListener("ui-visibility-changed", value);
  }
}

void Wings8AssistantWebUIHandler::OnNativeThemeUpdated(ui::NativeTheme* observed_theme) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  auto colors = wings8_assistant_app_ui_->delegate()->GetSystemColorInfo();
  base::Value::Dict value;
  value.Set("base", ui::ConvertSkColorToCSSColor(colors.base));
  value.Set("shaded", ui::ConvertSkColorToCSSColor(colors.shaded));
  value.Set("header", ui::ConvertSkColorToCSSColor(colors.header));
  value.Set("primary", ui::ConvertSkColorToCSSColor(colors.primary));
  FireWebUIListener("system-color-changed", value);
}

void Wings8AssistantWebUIHandler::OnConnectionChanged(network::mojom::ConnectionType type) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("network-connection-changed", base::Value(static_cast<int>(type)));
}

void Wings8AssistantWebUIHandler::OnBubbleQueryChanged(const Wings8AssistantViewObserver::ClipboardItemForAssistant& item) {
  if (!IsJavascriptAllowed()) {
    return;
  }
  if (item.display_text.size() > 0) {
    base::Value::Dict value;
    value.Set("query", item.display_text);
    value.Set("format", item.display_format);
    FireWebUIListener("query-from-bubble", value);
  }
}

void Wings8AssistantWebUIHandler::OnBubbleVisibilityChanged(bool visible)  {
  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("bubble-visibility-changed", base::Value(visible));
}

} // namespace ash
