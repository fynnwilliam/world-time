#pragma once

#include <string>
#include "timezn.h"
#include <unordered_map>

class timezns {
private:
  std::unordered_map<std::string, timezn> timezns_;

  void load() noexcept;

public:
  timezns() { load(); }

  auto find(std::string const&) const noexcept;
}
