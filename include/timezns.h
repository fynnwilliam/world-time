#pragma once

#include "timezn.h"
#include <unordered_map>

class timezns {
private:
  std::unordered_map<std::string, timezn> timezns_;

  load() noexcept;

public:
  timezns() { load(); }

  find() const noexcept;
}
