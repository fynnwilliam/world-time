#pragma once

#include "timezn.h"
#include <unordered_map>

class timezns {
private:
  std::unordered_map<std::string, timezn> timezns_;

public:
  timezns() {}

  read_zones() noexcept;
  find() const noexcept;
}
