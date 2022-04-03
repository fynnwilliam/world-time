#include "timezns.h"

void app::read_zones() {
  std::stringstream timezones{::timezones};
  std::string timezone;

  while (timezones >> timezone) {
    timezn temp = timezn().values(timezone);
    timezns_.insert({temp.name(), temp});
  }
}
