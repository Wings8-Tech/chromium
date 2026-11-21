// Copyright 2025 wings8 technology. All rights reserved

#ifndef CHROME_BROWSER_UI_WEBUI_ASH_LOGIN_WINGS8_LOCAL_SIGNIN_SCREEN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_ASH_LOGIN_WINGS8_LOCAL_SIGNIN_SCREEN_HANDLER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/webui/ash/login/base_screen_handler.h"

namespace ash {

class Key;

// WINGS8OS: Returns the access token captured at login, decrypted from the
// persistent OSCrypt store in local state (survives restarts).
std::string GetWings8OSAccessToken();

// WINGS8OS: Returns the refresh token captured at login (may be empty).
std::string GetWings8OSRefreshToken();

// WINGS8OS: Persists the auth tokens, OSCrypt-encrypted, into local state.
void StoreWings8OSAuthTokens(const std::string& access_token,
                           const std::string& refresh_token,
                           const std::string& email);

// WINGS8OS: Clears persisted auth tokens (used after a failed refresh).
void ClearWings8OSAuthTokens();

class Wings8LocalSigninView {
 public:
  inline constexpr static StaticOobeScreenId kScreenId{"wings8-local-signin",
                                                       "Wings8LocalSigninScreen"};

  virtual ~Wings8LocalSigninView() = default;

  // Shows the contents of the screen.
  virtual void Show() = 0;

  // Clear the input fields on the screen.
  virtual void Reset() = 0;

  // Set error state.
  virtual void SetErrorState(const std::string& username, int errorState) = 0;

  virtual base::WeakPtr<Wings8LocalSigninView> AsWeakPtr() = 0;
};

class Wings8LocalSigninScreenHandler : public Wings8LocalSigninView,
                                     public BaseScreenHandler {
 public:
  using TView = Wings8LocalSigninView;

  Wings8LocalSigninScreenHandler();
  ~Wings8LocalSigninScreenHandler() override;

  Wings8LocalSigninScreenHandler(const Wings8LocalSigninScreenHandler&) = delete;
  Wings8LocalSigninScreenHandler& operator=(const Wings8LocalSigninScreenHandler&) =
      delete;

  void Show() override;
  void Reset() override;
  void SetErrorState(const std::string& username, int errorState) override;
  base::WeakPtr<Wings8LocalSigninView> AsWeakPtr() override;

  void DeclareJSCallbacks() override;
  void DeclareLocalizedValues(
      ::login::LocalizedValuesBuilder* builder) override;

 private:
  void DoCompleteLogin(const bool newUser,
                       const std::string& username,
                       const std::string& password);
  void HandleCompleteAuth(const bool newUser,
                          const std::string& username,
                          const std::string& password,
                          const std::string& access_token = "",
                          const std::string& refresh_token = "");

  base::WeakPtrFactory<Wings8LocalSigninView> weak_ptr_factory_{this};
};

}  // namespace ash

#endif  // ifndef
        // CHROME_BROWSER_UI_WEBUI_ASH_LOGIN_WINGS8_LOCAL_SIGNIN_SCREEN_HANDLER_H_
