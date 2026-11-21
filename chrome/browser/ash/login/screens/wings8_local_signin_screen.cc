// Copyright 2022 Wings8 Technology. All rights reserved
#include "chrome/browser/ash/login/screens/wings8_local_signin_screen.h"
#include "chrome/browser/ui/webui/ash/login/wings8_local_signin_screen_handler.h"
#include "base/logging.h"

namespace ash {
namespace {

constexpr char kUserActionCancel[] = "cancel";
constexpr char kUserActionBackToUserSelection[] = "accountTypeSelectionBack";

}

std::string Wings8LocalSigninScreen::GetResultString(Result result) {
  switch (result) {
    case Result::CANCEL:
      return "Cancel";
    case Result::ACCOUNT_TYPE_SELECTION_BACK:
      return "Back";
    case Result::BACK:
      return "Back";
  }
}

Wings8LocalSigninScreen::Wings8LocalSigninScreen(
    base::WeakPtr<Wings8LocalSigninView> view,
    const base::RepeatingCallback<void(Result)>& exit_callback)
    : BaseScreen(Wings8LocalSigninView::kScreenId,
                 OobeScreenPriority::DEFAULT),
      view_(std::move(view)),
      exit_callback_(exit_callback) {}

Wings8LocalSigninScreen::~Wings8LocalSigninScreen() = default;

void Wings8LocalSigninScreen::ShowImpl() {
  if (!view_)
    return;
  view_->Show();
}

void Wings8LocalSigninScreen::HideImpl() {
  if (!view_)
    return;
  view_->Reset();
}

void Wings8LocalSigninScreen::OnUserAction(const base::Value::List& args) {
  const std::string& action_id = args[0].GetString();
  if (action_id == kUserActionCancel) {
    HandleCancel();
    return;
  } else if (action_id == kUserActionBackToUserSelection) {
    HandleBackToUserSelection();
    return;
  }
  BaseScreen::OnUserAction(args);
}

void Wings8LocalSigninScreen::HandleCancel() {
    view_->Reset();
    exit_callback_.Run(Result::CANCEL);
}

void Wings8LocalSigninScreen::HandleBackToUserSelection() {
  view_->Reset();
  LOG(INFO) << "Wings8LocalSigninScreen: Back to user selection";
  // Just use the exit callback - the parent controller will handle navigation
   exit_callback_.Run(Result::ACCOUNT_TYPE_SELECTION_BACK);
}

bool Wings8LocalSigninScreen::HandleAccelerator(LoginAcceleratorAction action) {
  return false;
}

}  // namespace ash
