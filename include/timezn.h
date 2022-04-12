#pragma once
#include <algorithm>
#include <sstream>
#include <string>

namespace world_time {
class timezn {
private:
  std::string name_;
  std::string region_;
  std::string location_;
  std::string area_;

  std::string try_insert_slash(std::string const &) const;

public:
  timezn values(std::string &);
  std::string sub_link() const;
  auto const &name() const noexcept { return name_; }
  auto const &region() const noexcept { return region_; }
  auto const &location() const noexcept { return location_; }
  auto const &area() const noexcept { return area_; }
};
} // namespace world_time
