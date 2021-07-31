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
    inline std::string name() const { return name_; }
    inline std::string region() const { return region_; }
    inline std::string location() const { return location_; }
    inline std::string area() const { return area_; }
};