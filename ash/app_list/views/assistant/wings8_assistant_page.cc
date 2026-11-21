#include "ash/app_list/views/assistant/wings8_assistant_page.h"
#include "ash/public/cpp/assistant/controller/assistant_ui_controller.h"
#include "ash/assistant/model/assistant_ui_model.h"
#include "ui/views/border.h"
#include "ui/views/layout/fill_layout.h"
#include "ash/public/cpp/ash_web_view_factory.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ash/assistant/util/deep_link_util.h"

namespace ash {

namespace {
const char kWings8AssistantExtensionUrl[] = "chrome://wings8os-ai/?source=launcher";
constexpr int kHeightDip = 440;

const bool disable_wings8_assistant_page = true;
} // namespace

Wings8AssistantPage::Wings8AssistantPage() {
  InitLayout();
  assistant_controller_observation_.Observe(AssistantController::Get());
  AssistantUiController::Get()->GetModel()->AddObserver(this);
}

Wings8AssistantPage::~Wings8AssistantPage() {
  if (AssistantUiController::Get())
    AssistantUiController::Get()->GetModel()->RemoveObserver(this);
}

void Wings8AssistantPage::OnBoundsChanged(
    const gfx::Rect& previous_bounds) {
  if (AssistantUiController::Get())
    AssistantUiController::Get()->SetAppListBubbleWidth(size().width());
}

void Wings8AssistantPage::RequestFocus() {
  VLOG(2) << "Wings8AssistantPage::RequestFocus()";
  if (web_view_ptr_) {
    web_view_ptr_->GetInitiallyFocusedView()->RequestFocus();
  }
}

void Wings8AssistantPage::InitLayout() {
  SetLayoutManager(std::make_unique<views::FillLayout>());
}

AshWebView* Wings8AssistantPage::WebView() {
  return web_view_ptr_ ? web_view_ptr_.get() : web_view_.get();
}

void Wings8AssistantPage::OnDeepLinkReceived(
    assistant::util::DeepLinkType type,
    const std::map<std::string, std::string>& params) {
  if (disable_wings8_assistant_page) {
    return;
  }
  if (type == assistant::util::DeepLinkType::kQuery) {
    const std::optional<std::string>& query =
        GetDeepLinkParam(params, assistant::util::DeepLinkParam::kQuery);

    if (!query.has_value())
      return;
    AssistantUiController::Get()->ShowUi(assistant::AssistantEntryPoint::kDeepLink);
    OpenUrl(GURL(base::StringPrintf("%s&initQuery=%s", kWings8AssistantExtensionUrl, query->c_str())));
  }
}

void Wings8AssistantPage::OnUiVisibilityChanged(
      AssistantVisibility new_visibility,
      AssistantVisibility old_visibility,
      std::optional<AssistantEntryPoint> entry_point,
      std::optional<AssistantExitPoint> exit_point) {
  if (disable_wings8_assistant_page) {
    return;
  }
  if (new_visibility == AssistantVisibility::kVisible && entry_point.has_value() && (entry_point == AssistantEntryPoint::kHotkey || entry_point == AssistantEntryPoint::kLauncherSearchBoxIcon)) {
    OpenUrl(GURL(kWings8AssistantExtensionUrl));
  }
}

void Wings8AssistantPage::InitializeUIForBubbleView() {
  // called from AppListBubbleView::InitializeUIForBubbleView
  VLOG(2) << "Wings8AssistantPage::InitializeUIForBubbleView()";
}

gfx::Size Wings8AssistantPage::CalculatePreferredSize(const views::SizeBounds& available_size) const {
  return gfx::Size(INT_MAX, kHeightDip);
}

void Wings8AssistantPage::OpenUrl(const GURL& url) {
  if (disable_wings8_assistant_page) {
    return;
  }
  if (web_view_ptr_ || web_view_) {
    return;
  }
  // RemoveContents();
  auto params = AshWebView::InitParams();
  params.can_record_media = true;
  web_view_ = AshWebViewFactory::Get()->Create(params);
  WebView()->AddObserver(this);
  WebView()->Navigate(url);
}

void Wings8AssistantPage::DidStopLoading() {
  if (!web_view_) {
    return;
  }

  web_view_->SetPreferredSize(GetPreferredSize());
  web_view_ptr_ = AddChildView(std::move(web_view_));
  web_view_ptr_->SetBorder(views::CreateEmptyBorder(0));
  web_view_ptr_->GetInitiallyFocusedView()->RequestFocus();
}

void Wings8AssistantPage::RemoveContents() {
  if (!web_view_ptr_) {
    return;
  }
  RemoveChildViewT(web_view_ptr_.get())->RemoveObserver(this);
  web_view_ptr_ = nullptr;
}

BEGIN_METADATA(Wings8AssistantPage)
END_METADATA

} // namespace ash
