// Copyright 2025 The wings8 technology. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/wings8os_ai/wings8os_ai_view.h"
#include "ash/constants/ash_features.h"
#include "base/check.h"
#include "base/logging.h"
#include "base/memory/ptr_util.h"
#include "base/time/time.h"
#include "ui/events/types/event_type.h"
#include "ui/views/background.h"
#include "ui/views/controls/label.h"
#include "ash/shell.h"
#include "ash/session/session_controller_impl.h"
#include "ash/public/cpp/ash_web_view_factory.h"
#include "ash/wings8os_ai/wings8os_ai_bubble.h"
#include "ui/wm/core/coordinate_conversion.h"
#include "base/task/task_traits.h"
#include "base/task/single_thread_task_runner.h"

namespace ash {

namespace {
const int kBubbleInitDelaySeconds = 5;
}

Wings8AssistantView::Wings8AssistantView(aura::Window* container): window_(container) {
  Shell::Get()->session_controller()->AddObserver(this);
  Shell::Get()->AddPreTargetHandler(this);
  AssistantState::Get()->AddObserver(this);
}

Wings8AssistantView::~Wings8AssistantView() {
  if (Shell::Get()) {
    Shell::Get()->RemovePreTargetHandler(this);
    Shell::Get()->session_controller()->RemoveObserver(this);
  }
  if (AssistantState::Get()) {
    AssistantState::Get()->RemoveObserver(this);
  }
}

bool Wings8AssistantView::IsVisible() const {
  return bubble_ && bubble_->GetWidget()->IsVisible();
}

void Wings8AssistantView::AddObserver(Wings8AssistantViewObserver* observer) const {
  observers_.AddObserver(observer);
}
void Wings8AssistantView::RemoveObserver(Wings8AssistantViewObserver* observer) const {
  observers_.RemoveObserver(observer);
}

void Wings8AssistantView::InitializeBubble() {
  if (bubble_initialized_) return;
  bubble_ = new Wings8AssistantBubble(window_, gfx::Rect(display::Screen::GetScreen()->GetCursorScreenPoint(), gfx::Size()));
  bubble_->InitWebView(this);
  bubble_initialized_ = true;
}

void Wings8AssistantView::ScheduleInitializeBubble() {
  if (bubble_initialized_ || init_scheduled_) return;
  if (Wings8AssistantBubble::ReadyToInit()) {
    InitializeBubble();
  } else {
    VLOG(2) << "Not ready to init bubble, schedule it, after " << kBubbleInitDelaySeconds << " seconds";
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&Wings8AssistantView::InitializeBubble,
                      weak_factory_.GetWeakPtr()),
        base::Seconds(kBubbleInitDelaySeconds));
    init_scheduled_ = true;
  }
}

void Wings8AssistantView::ShowBubble(bool update_anchor_point) {
  if (!enabled_) {
    return;
  }
  if (IsVisible()) {
    return;
  }
  Show(update_anchor_point);
}

void Wings8AssistantView::ProcessPressedEvent(ui::LocatedEvent* event) {
  if (!bubble_) return;
  gfx::Point screen_location = event->location();
  ::wm::ConvertPointToScreen(static_cast<aura::Window*>(event->target()),
                             &screen_location);
  if (bubble_->GetBoundsInScreen().Contains(screen_location)) {
    return;
  }
  Hide();
}

void Wings8AssistantView::ResetDragStartPoint(ui::LocatedEvent* event) {
  if (is_dragging_) {
    is_dragging_ = false;
    event->SetHandled();
  }
  drag_start_point_ = gfx::Point();
}

void Wings8AssistantView::ProcessDraggedEvent(ui::LocatedEvent* event) {
  if (!IsVisible()) return;
  gfx::Point screen_location = event->location();
  ::wm::ConvertPointToScreen(static_cast<aura::Window*>(event->target()),
                             &screen_location);
  if (!bubble_->GetBoundsInScreen().Contains(screen_location)) {
    return;
  }
  gfx::Rect widget_bounds = bubble_->GetWidget()->GetWindowBoundsInScreen();
  if (!drag_start_point_.IsOrigin()) {
    widget_bounds.Offset(screen_location - drag_start_point_);
    bubble_->GetWidget()->SetBounds(widget_bounds);
    is_dragging_ = true;
    event->SetHandled();
  }
  drag_start_point_ = screen_location;
}

void Wings8AssistantView::OnTouchEvent(ui::TouchEvent* event) {
  if (event->type() == ui::EventType::kTouchPressed) {
    ProcessPressedEvent(event->AsLocatedEvent());
  } else if (event->type() == ui::EventType::kTouchMoved) {
    ProcessDraggedEvent(event->AsLocatedEvent());
  } else if (event->type() == ui::EventType::kTouchReleased || event->type() == ui::EventType::kTouchCancelled) {
    ResetDragStartPoint(event->AsLocatedEvent());
  }
}

void Wings8AssistantView::OnMouseEvent(ui::MouseEvent* event) {
  if (event->type() == ui::EventType::kMousePressed) {
    ProcessPressedEvent(event->AsLocatedEvent());
  } else if (event->type() == ui::EventType::kMouseDragged) {
    ProcessDraggedEvent(event->AsLocatedEvent());
  } else if (event->type() == ui::EventType::kMouseReleased) {
    ResetDragStartPoint(event->AsLocatedEvent());
  }
}

void Wings8AssistantView::HideBubble() {
  if (!IsVisible()) {
    return;
  }
  Hide();
}

void Wings8AssistantView::Show(bool update_anchor_point) {
  if (!ready_to_show_bubble_) {
    return;
  }
  if (!bubble_) {
    return;
  }
  if (update_anchor_point) {
    current_anchor_point_ = display::Screen::GetScreen()->GetCursorScreenPoint();
  }
  bubble_->SetAnchorRect(gfx::Rect(current_anchor_point_, gfx::Size()));
  bubble_->SetPreferredSize(bubble_->CalculatePreferredSize({}));
  bubble_->GetWidget()->Show();
  for (auto& observer : observers_) {
    observer.OnBubbleVisibilityChanged(IsVisible());
    observer.OnBubbleQueryChanged(last_clipboard_item_);
  }
}

void Wings8AssistantView::Hide() {
  if (!bubble_) {
    return;
  }
  bubble_->SetPreferredSize(bubble_->CalculatePreferredSize({}));
  bubble_->GetWidget()->Hide();
  for (auto& observer : observers_) {
    observer.OnBubbleVisibilityChanged(IsVisible());
  }
}

void Wings8AssistantView::OnSessionStateChanged(session_manager::SessionState state) {
  if (enabled_ && state == session_manager::SessionState::ACTIVE) {
    ScheduleInitializeBubble();
  }
}

void Wings8AssistantView::OnChromeTerminating() {
  if (bubble_) {
    bubble_->RemoveWebView();
  }
}

void Wings8AssistantView::OnWings8AssistantExtraAcceleratorEnabled(bool enabled) {
  enabled_ = enabled;

  if (enabled_) {
    ScheduleInitializeBubble();
  }
}

void Wings8AssistantView::HandleSendTextToAI(const gfx::Rect& anchor_rect, const std::u16string& text) {
  if (!enabled_) {
    return;
  }
  if (text.empty()) {
    return;
  }
  last_clipboard_item_.display_format = static_cast<int>(crosapi::mojom::ClipboardHistoryDisplayFormat::kText);
  last_clipboard_item_.display_text = text;

  current_anchor_point_ = anchor_rect.origin();
  ShowBubble(false);
}

void Wings8AssistantView::UpdateLastClipboardItem(const ClipboardHistoryItem& item) {
  if (!enabled_) {
    return;
  }
  VLOG(3) << "clipboard update";
  last_clipboard_item_time_ = base::TimeTicks::Now();
  last_clipboard_item_.display_format = static_cast<int>(item.display_format());
  last_clipboard_item_.display_text = item.display_text();
  // copy from subsystem can be slow,  slower than the gap between pressing ctrl+c and c twice
  auto now = base::TimeTicks::Now();
  if (now - last_time_triggered_ < base::Seconds(1) && should_show_bubble_delay_) {
    VLOG(3) << "pressed twice and clipboard updated, show the bubble now";
    ShowBubble();
  }
}

bool Wings8AssistantView::CanHandleTouchSelectionMenuAction() {
  if (!enabled_) {
    return false;
  }
  if (!ready_to_show_bubble_) {
    return false;
  }
  return true;
}

bool Wings8AssistantView::CanHandleToggleWings8OSAssistant() {
  if (!enabled_) {
    return false;
  }
  if (!ready_to_show_bubble_) {
    return false;
  }
  auto now = base::TimeTicks::Now();
  auto delta = now - last_time_triggered_;
  VLOG(3) << "wings8os assistant view accelerator, time delta: " << delta.InMilliseconds();
  bool triggered_before_clipboard_update = last_clipboard_item_time_ < last_time_triggered_;
  last_time_triggered_ = now;
  bool repeated = delta < base::Seconds(1);
  if (repeated && triggered_before_clipboard_update) {
    VLOG(3) << "wings8os assistant accelerator pressed twice, but clipboard not updated, so the bubble should be shown later";
    should_show_bubble_delay_ = true;
    return false;
  }
  should_show_bubble_delay_ = false;
  VLOG(3) << "can handle wings8os assistant accelerator: " << repeated;
  return repeated;
}

void Wings8AssistantView::OnBubbleReady() {
  ready_to_show_bubble_ = true;
}

void Wings8AssistantView::SetBubbleRect(int x, int y, int width, int height) {
  if (bubble_) {
    VLOG(3) << "set bubble rect: " << x << ", " << y << ", " << width << ", " << height;
    auto current = bubble_->GetWidget()->GetWindowBoundsInScreen();
    auto newRect = gfx::Rect(
      x > 0 ? x : current.x(),
      y > 0 ? y : current.y(),
      width > 0 ? width : current.width(),
      height > 0 ? height : current.height()
    );
    bubble_->SetPreferredSize(gfx::Size(newRect.width(), newRect.height()));
    bubble_->SetAnchorRect(gfx::Rect(current_anchor_point_, gfx::Size()));
  }
}

void Wings8AssistantView::CenterBubble(int width, int height) {
  if (bubble_) {
    bubble_->GetWidget()->CenterWindow(gfx::Size(width, height));
  }
}

} // namespace ash
