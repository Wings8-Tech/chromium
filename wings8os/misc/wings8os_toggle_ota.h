#ifndef WINGS8OS_TOGGLE_OTA_H_
#define WINGS8OS_TOGGLE_OTA_H_

#include "base/functional/callback_forward.h"

namespace wings8os {
namespace misc {
  void EnableWings8OTA(const bool enabled, base::OnceCallback<void()> callback);
  bool GetEnabledWings8OTA();
} // misc

} // wings8os
#endif /* ifndef WINGS8OS_TOGGLE_OTA_H_ */
