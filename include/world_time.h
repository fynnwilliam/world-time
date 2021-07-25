#pragma once
#include <regex>
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
    std::string sub_link() const;
    std::string name() const { return name_; }
    std::string region() const { return region_; }
    std::string location() const { return location_; }
    std::string area() const { return area_; }
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

std::string insert_slash(std::string item);
std::string timezn::sub_link() const
{
    return std::string{"/timezone"} + insert_slash(region()) + insert_slash(location()) + insert_slash(area());
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

bool private_a(std::string const&);
bool private_b(std::string const&);
bool private_c(std::string const&);
bool private_ip(std::string const&);
bool public_ip(std::string const&);
bool ip_address(std::string const&);

void display_time(std::stringstream& ss, std::string input)
{
    std::string sch;
    int count{};
    
    while (ss >> sch)
        if (count++ == 5)
            std::cout << "It is " << sch.substr(sch.find('T') + 1, 8) << (ip_address(input) ? " at " : " in ") << input << '\n';
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
    
    if (ip_address(argv[1]))
    { 
        if (argc > 2) { throw invalid_argc(); }
        
        std::string ip{argv[1]};
        
        if (public_ip(ip)) { return ip; }
        else { throw std::out_of_range(ip + " is not a public IP"); }
    }
    
    std::string first = !argv[1] ? throw invalid_argc() : argv[1];
    std::string second = !argv[2] ? std::string{} : argv[2];
  
    return second.empty() ? first : first.append('_' + second);
}

std::string insert_slash(std::string item)
{
    return item.empty() ? item : '/' + item;
}

std::string find_timezone(std::string usr_input)
{
    if (ip_address(usr_input)) { return std::string{"/ip/"}.append(usr_input); }

    for (timezn& a : timezns)
        {   
             if (to_lower(a.name()) == to_lower(usr_input))
             {
                  return a.sub_link();
             }
        }
        
        return std::string{};
}

auto not_avaliable = []() { return std::range_error("timezone not found"); };

bool private_a(std::string const& ip)
{
    std::regex pattern("([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
    return std::regex_match(ip, pattern);
}

bool private_b(std::string const& ip)
{
    std::regex pattern("([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}");
    return std::regex_match(ip, pattern);
}

bool private_c(std::string const& ip)
{
    std::regex pattern("([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}");
    return std::regex_match(ip, pattern);
}

bool private_ip(std::string const& ip)
{
    return private_a(ip) || private_b(ip) || private_c(ip);
}

bool public_ip(std::string const& ip)
{
    return !private_ip(ip);
}

bool ip_address(std::string const& item)
{
    std::regex pattern("([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
    return std::regex_match(item, pattern);
}