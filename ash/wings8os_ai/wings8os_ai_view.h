#ifndef ASH_WINGS8OS_AI_WINGS8OS_AI_VIEW_H_
#define ASH_WINGS8OS_AI_WINGS8OS_AI_VIEW_H_

#include <memory>
#include "ash/ash_export.h"
#include "ash/clipboard/clipboard_history_item.h"
#include "base/memory/raw_ptr.h"
#include "ash/public/cpp/session/session_observer.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "ui/events/event.h"
#include "ui/events/event_handler.h"
#include "ash/public/cpp/assistant/assistant_state.h"

namespace views {
class View;
}

namespace aura {
class Window;
}

namespace ash {

class Wings8AssistantViewObserver : public base::CheckedObserver  {
 public:
  struct ClipboardItemForAssistant {
    std::u16string display_text;
    int            display_format;
  };

  Wings8AssistantViewObserver(const Wings8AssistantViewObserver&) = delete;
  Wings8AssistantViewObserver& operator=(const Wings8AssistantViewObserver&) = delete;

  virtual void OnBubbleQueryChanged(const ClipboardItemForAssistant& item) {}
  virtual void OnBubbleVisibilityChanged(bool visible) {}
 protected:
  Wings8AssistantViewObserver() = default;
  ~Wings8AssistantViewObserver() override = default;
};

class Wings8AssistantBubble;

class ASH_EXPORT Wings8AssistantView : public SessionObserver, public ui::EventHandler,
                                     public AssistantStateObserver {
 public:
  explicit Wings8AssistantView(aura::Window* container);

  Wings8AssistantView(const Wings8AssistantView&) = delete;
  Wings8AssistantView& operator=(const Wings8AssistantView&) = delete;

  ~Wings8AssistantView() override;

  void AddObserver(Wings8AssistantViewObserver* observer) const;
  void RemoveObserver(Wings8AssistantViewObserver* observer) const;

  bool IsVisible() const;

  void ShowBubble(bool update_anchor_point = true);
  void HideBubble();

  void UpdateLastClipboardItem(const ClipboardHistoryItem& item);
  bool CanHandleToggleWings8OSAssistant();

  bool CanHandleTouchSelectionMenuAction();
  void HandleSendTextToAI(const gfx::Rect& anchor_rect, const std::u16string& text);

  void OnBubbleReady();

  void SetBubbleRect(int x, int y, int width, int height);

  void CenterBubble(int width, int height);

 private:
  void OnSessionStateChanged(session_manager::SessionState state) override;
  void OnChromeTerminating() override;

  void OnMouseEvent(ui::MouseEvent* event) override;
  void OnTouchEvent(ui::TouchEvent* event) override;

  void ProcessPressedEvent(ui::LocatedEvent* event);
  void ProcessDraggedEvent(ui::LocatedEvent* event);

  void ResetDragStartPoint(ui::LocatedEvent* event);

  void OnWings8AssistantExtraAcceleratorEnabled(bool enabled) override;

  void Show(bool update_anchor_point);
  void Hide();

  void InitializeBubble();
  void ScheduleInitializeBubble();

  bool init_scheduled_ = false;
  bool enabled_ = false;
  bool ready_to_show_bubble_ = false;
  bool bubble_initialized_ = false;
  bool should_show_bubble_delay_ = false;
  base::TimeTicks last_clipboard_item_time_ = base::TimeTicks::Min();
  base::TimeTicks last_time_triggered_ = base::TimeTicks::Min();
  Wings8AssistantViewObserver::ClipboardItemForAssistant last_clipboard_item_;
  raw_ptr<Wings8AssistantBubble, DanglingUntriaged> bubble_;

  raw_ptr<aura::Window, DanglingUntriaged> window_ = nullptr;

  gfx::Point current_anchor_point_;
  gfx::Point drag_start_point_;
  bool is_dragging_ = false;

  mutable base::ObserverList<Wings8AssistantViewObserver> observers_;

base::WeakPtrFactory<Wings8AssistantView> weak_factory_{this};
};

}  // namespace ash

#endif // !ASH_WINGS8OS_AI_WINGS8OS_AI_VIEW_H_
