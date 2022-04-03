#pragma once

#include "timezn.h"
#include <string>
#include <unordered_map>

class timezns {
private:
  std::unordered_map<std::string, timezn> timezns_;

  void load() noexcept;
  auto &to_upper(std::string &) const noexcept;
  auto try_uppercase(std::string &) const noexcept;

public:
  timezns() { load(); }

  auto find(std::string &) const noexcept;
};
