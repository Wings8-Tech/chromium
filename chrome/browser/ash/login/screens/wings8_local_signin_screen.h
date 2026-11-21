// Copyright 2022 Wings8 Technology. All rights reserved

#ifndef CHROME_BROWSER_ASH_LOGIN_SCREENS_WINGS8_LOCAL_SIGNIN_SCREEN_H_
#define CHROME_BROWSER_ASH_LOGIN_SCREENS_WINGS8_LOCAL_SIGNIN_SCREEN_H_

#include <string>
#include "base/functional/callback.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ash/login/screens/base_screen.h"
#include "chrome/browser/ui/webui/ash/login/wings8_local_signin_screen_handler.h"

namespace ash {

class Wings8LocalSigninScreen
    : public BaseScreen {
  public:
    enum class Result { CANCEL, ACCOUNT_TYPE_SELECTION_BACK, BACK };
    
    static std::string GetResultString(Result result);
    
    Wings8LocalSigninScreen(base::WeakPtr<Wings8LocalSigninView> view,
                          const base::RepeatingCallback<void(Result)>& exit_callback);

    ~Wings8LocalSigninScreen() override;

    Wings8LocalSigninScreen(const Wings8LocalSigninScreen&) = delete;
    Wings8LocalSigninScreen& operator=(const Wings8LocalSigninScreen&) = delete;

  private:
    void HandleCancel();
    void HandleBackToUserSelection();

    // BaseScreen:
    void ShowImpl() override;
    void HideImpl() override;
    void OnUserAction(const base::Value::List& args) override;
    bool HandleAccelerator(LoginAcceleratorAction action) override;

    base::WeakPtr<Wings8LocalSigninView> view_;

    base::RepeatingCallback<void(Result)> exit_callback_;

    base::WeakPtrFactory<Wings8LocalSigninScreen> weak_factory_{this};
};

}

namespace chromeos {
using ::ash::Wings8LocalSigninScreen;
}
#endif // ifndef CHROME_BROWSER_ASH_LOGIN_SCREENS_WINGS8_LOCAL_SIGNIN_SCREEN_H_
