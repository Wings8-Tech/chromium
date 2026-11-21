#ifndef ASH_WINGS8OS_AI_WINGS8OS_AI_BUBBLE_H_
#define ASH_WINGS8OS_AI_WINGS8OS_AI_BUBBLE_H_

#include "ash/ash_export.h"
#include "ash/wings8os_ai/wings8os_ai_view.h"
#include "ui/views/bubble/bubble_dialog_delegate_view.h"
#include "ash/public/cpp/ash_web_view.h"

namespace aura {
class Window;
}

namespace ash {

class ASH_EXPORT Wings8AssistantBubble : public views::BubbleDialogDelegateView,
                                       public AshWebView::Observer {
 public:
  static bool ReadyToInit();

  explicit Wings8AssistantBubble(aura::Window* container, const gfx::Rect& anchor_rect);

  Wings8AssistantBubble(const Wings8AssistantBubble&) = delete;
  Wings8AssistantBubble& operator=(const Wings8AssistantBubble&) =
      delete;
  ~Wings8AssistantBubble() override;

  bool InitWebView(Wings8AssistantView* owner);

  void RemoveWebView();

  // views::BubbleDialogDelegateView:
  gfx::Size CalculatePreferredSize(const views::SizeBounds& available_size) const override;

 private:
  void OnThemeChanged() override;
  // AshWebView::Observer:
  void DidStopLoading() override;

  bool OpenUrl(const GURL& url);

  std::unique_ptr<AshWebView> web_view_;
  raw_ptr<AshWebView, DanglingUntriaged> web_view_ptr_ = nullptr;
  raw_ptr<Wings8AssistantView> owner_ = nullptr;
};

}

#endif // !ASH_WINGS8OS_AI_WINGS8OS_AI_BUBBLE_H_
