#include "timezns.h"
#include "timezones.h"

namespace world_time {
void timezns::load() noexcept {
  std::stringstream timezones{::timezones};
  std::string timezone;

  timezns_.reserve(400);

  while (timezones >> timezone) {
    timezn temp = timezn().values(timezone);
    timezns_.try_emplace(temp.name(), temp);
  }
}

std::string timezns::find(std::string &zone) const noexcept {
  auto t = timezns_.find(zone);
  return t == timezns_.end() ? try_uppercase(zone) : t->second.sub_link();
}

auto &timezns::to_upper(std::string &s) const noexcept {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return s;
}

std::string timezns::try_uppercase(std::string &zone) const noexcept {
  auto t = timezns_.find(to_upper(zone));
  return t == timezns_.end() ? std::string{} : t->second.sub_link();
}
} // namespace world_time
