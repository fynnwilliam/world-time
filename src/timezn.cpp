#include "timezn.h"

namespace world_time {
timezn timezn::values(std::string &timezone) {
  std::replace(timezone.begin(), timezone.end(), '/', ' ');
  std::stringstream temp(timezone);
  temp >> region_ >> location_ >> area_;

  name_ = area_ == location_ ? region_ : area_.empty() ? location_ : area_;

  return *this;
}

std::string timezn::sub_link() const {
  return std::string{"/timezone"} + try_insert_slash(region()) +
         try_insert_slash(location()) + try_insert_slash(area());
}

std::string timezn::try_insert_slash(std::string const &item) const {
  return item.empty() ? item : '/' + item;
}
} // namespace world_time
