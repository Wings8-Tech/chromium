// Copyright 2025 The wings8 technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/wings8os_ai/wings8os_ai_bubble.h"
#include "base/strings/utf_string_conversions.h"
#include "net/base/url_util.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/aura/window.h"
#include "ash/public/cpp/shell_window_ids.h"
#include "ash/bubble/bubble_constants.h"
#include "ui/views/highlight_border.h"
#include "ui/chromeos/styles/cros_tokens_color_mappings.h"
#include "ash/public/cpp/ash_web_view_factory.h"
#include "ash/assistant/util/deep_link_util.h"
#include "ash/public/cpp/assistant/controller/assistant_controller.h"

namespace ash {

namespace {

const char kWings8AssistantExtensionUrl[] = "chrome://wings8os-ai/bubble?source=bubble";
constexpr int kWidthDip = 300;
constexpr int kHeightDip = 162;

}

Wings8AssistantBubble::~Wings8AssistantBubble() = default;

// static
bool Wings8AssistantBubble::ReadyToInit() {
  return AshWebViewFactory::Get() != nullptr;
}

gfx::Size Wings8AssistantBubble::CalculatePreferredSize(const views::SizeBounds& available_size) const {
  return gfx::Size(kWidthDip, kHeightDip);
}

void Wings8AssistantBubble::OnThemeChanged() {
  views::BubbleDialogDelegateView::OnThemeChanged();
  set_color(
      GetColorProvider()->GetColor(cros_tokens::kCrosSysSystemBaseElevated));
}

Wings8AssistantBubble::Wings8AssistantBubble(aura::Window* window, const gfx::Rect& anchor_rect) {
  SetAnchorRect(anchor_rect);
  SetButtons(static_cast<int>(ui::mojom::DialogButton::kNone));
  set_margins(gfx::Insets());
  // control hide/show on  my own
  set_close_on_deactivate(false);
  set_parent_window(window);
  SetLayoutManager(std::make_unique<views::FillLayout>());

  CreateBubble(this);
  GetBubbleFrameView()->SetCornerRadius(kBubbleCornerRadiusForAI);
  GetBubbleFrameView()->SetBackgroundColor(color());
  // views::DialogDelegate::CreateDialogWidget(this, nullptr, window);
}

bool Wings8AssistantBubble::InitWebView(Wings8AssistantView* owner) {
  owner_ = owner;
  return OpenUrl(GURL(kWings8AssistantExtensionUrl));
}

void Wings8AssistantBubble::RemoveWebView() {
  if (web_view_ptr_) {
    RemoveChildViewT(web_view_ptr_.get())->RemoveObserver(this);
    web_view_ptr_ = nullptr;
  }
}

bool Wings8AssistantBubble::OpenUrl(const GURL& url) {
  if (web_view_ptr_ || web_view_) {
    return true;
  }
  auto params = AshWebView::InitParams();
  params.can_record_media = true;
  if (!Wings8AssistantBubble::ReadyToInit()) {
    return false;
  }
  web_view_ = AshWebViewFactory::Get()->Create(params);
  web_view_->AddObserver(this);
  web_view_->Navigate(url);
  return true;
}

void Wings8AssistantBubble::DidStopLoading()  {
  if (!web_view_) {
    return;
  }

  web_view_->SetPreferredSize(GetPreferredSize());
  web_view_ptr_ = AddChildView(std::move(web_view_));
  web_view_ptr_->SetBorder(views::CreateEmptyBorder(0));
  web_view_ptr_->GetInitiallyFocusedView()->RequestFocus();

  owner_->OnBubbleReady();
}

}
