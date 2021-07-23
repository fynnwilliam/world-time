#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>

class timezn
{
private:    
    std::string name_;
    std::string region_;
    std::string location_;
    std::string area_;
    
public:    
    timezn values(std::string& timezone);
    std::string& name() { return name_; }
    std::string& region() { return region_; }
    std::string& location() { return location_; }
    std::string& area() { return area_; }
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

void display_time(std::stringstream& ss, std::string input)
{
    std::string sch;
    int count{};
    
    while (ss >> sch)
        if (count++ == 5)
            std::cout << "the time in " << input << " is "<< sch.substr(sch.find('T') + 1, 8) << '\n';
}

std::string to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return s;
}

auto invalid_argc()
{
    return std::invalid_argument("invalid number of arguments");
}

std::string arguments(int argc, char* argv[])
{
    if (argc > 3) { throw invalid_argc(); }
    
    std::string first = !argv[1] ? throw invalid_argc() : argv[1];
    std::string second = !argv[2] ? std::string{} : argv[2];
  
    return second.empty() ? first : first.append('_' + second);
}

std::string append(std::string& item)
{
    return item.empty() ? item : '/' + item;
}

std::string find_timezone(std::string usr_input)
{
    for (timezn& a : timezns)
        {   
             if (to_lower(a.name()) == to_lower(usr_input))
             {
                  return std::string{"/timezone"} + append(a.region()) + append(a.location()) + append(a.area());
             }
        }
        
        return std::string{};
}

auto not_avaliable = []() { return std::range_error("timezone not found"); };