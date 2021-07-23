#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

class timezn
{
private:    
    std::string name_;
    std::string region_;
    std::string location_;
    std::string area_;
    
public:    
    timezn values(std::string& timezone);
    std::string name() { return name_; }
    std::string region() { return region_; }
    std::string location() { return location_; }
    std::string area() { return area_; }
};

std::vector<timezn> timezns;

timezn timezn::values(std::string& timezone)
{
    std::replace(timezone.begin(), timezone.end(), '/', ' ');
    std::stringstream temp(timezone);
    temp >> region_ >> location_ >> area_;

    name_ = area_ == location_ ? region_ : area_.size() == 0 ? location_ : area_;

    return *this;
}

void read_timezones()
{
    std::ifstream timezones("../timezones");
    std::string timezone;

    while (timezones >> timezone)
    {
        timezns.push_back(timezn().values(timezone));
    }
}

void display_time(std::stringstream& ss)
{
    std::string sch;
    int count{};
    
    while (ss >> sch)
        if (count++ == 5)
            std::cout << "the time in ... is " << sch.substr(sch.find('T') + 1, 8) << '\n';
}

std::string to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return s;
}

std::string arguments(char* argv[])
{
    std::string first = argv[1] == 0 ? throw std::runtime_error("...") : argv[1];
    std::string second = argv[2] == 0 ? "" : argv[2];
  
    return second.empty() ? first : first.append('_' + second);
}

// http://worldtimeapi.org/api/timezone/