#pragma once

#include "timezn.h"
#include <unordered_map>

class timezns {
private:
  std::unordered_map<std::string, timezn> timezns_;

  void load() noexcept;
  auto &to_upper(std::string &) const noexcept;
  std::string try_uppercase(std::string &) const noexcept;

public:
  timezns() { load(); }

  std::string find(std::string &) const noexcept;
};
