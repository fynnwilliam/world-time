#pragma once
#include <string>
#include <sstream>
#include <algorithm>

class timezn
{
private:
    std::string name_;
    std::string region_;
    std::string location_;
    std::string area_;
    
    std::string insert_slash(std::string) const;

public:
    timezn values(std::string&);
    std::string sub_link() const;
    inline auto const& name() const noexcept { return name_; }
    inline auto const& region() const noexcept { return region_; }
    inline auto const& location() const noexcept { return location_; }
    inline auto const& area() const noexcept { return area_; }
};