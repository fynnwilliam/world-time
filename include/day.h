#pragma once

#include <string>
#include <vector>

namespace world_time {
class day {
private:
  std::vector<std::string> const days_{"Sunday",    "Monday",   "Tuesday",
                                       "Wednesday", "Thursday", "Friday",
                                       "Saturday"};

public:
  std::string operator[](std::size_t day) const noexcept {
    return day < days_.size() ? std::string{", "} + days_[day]
                              : std::string{", Unknown_day"};
  }
};
} // namespace world_time
