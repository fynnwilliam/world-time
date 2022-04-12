#pragma once

#include <string>
#include <vector>

namespace world_time {
class month {
private:
  std::vector<std::string> const months_{
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};

public:
  std::string operator[](std::size_t m) const noexcept {
    return m && m <= months_.size() ? std::string{", "} + months_[m - 1]
                                    : std::string{", Unknown_month"};
  }
};
} // namespace world_time
