#include "timezns.h"

void timezns::load() noexcept {
  std::stringstream timezones{::timezones};
  std::string timezone;

  while (timezones >> timezone) {
    timezn temp = timezn().values(timezone);
    timezns_.insert({temp.name(), temp});
  }
}

auto timezns::find(std::string const& zone) const noexcept {
  auto t = timezns_.find(zone);
  return t == timezns_.end() ? try_uppercase() : t->second.sub_link();
}
