#pragma once
#include <regex>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

class timezn
{
private:
    std::string name_;
    std::string region_;
    std::string location_;
    std::string area_;

public:
    timezn values(std::string&);
    std::string sub_link() const;
    inline std::string name() const { return name_; }
    inline std::string region() const { return region_; }
    inline std::string location() const { return location_; }
    inline std::string area() const { return area_; }
};

void retrieve_time(int const&, char**);
void read_timezones();
void display_time(std::stringstream&, std::string const&);
auto invalid_argc();
auto not_avaliable();
bool private_a(std::string const&);
bool private_b(std::string const&);
bool private_c(std::string const&);
bool private_ip(std::string const&);
bool public_ip(std::string const&);
bool ip_address(std::string const&);
std::string url(std::string const&);
std::string to_lower(std::string);
std::string insert_slash(std::string);
std::string ip(int const&, char**);
std::string location(char**);
std::string arguments(int const&, char**);
std::string insert_slash(std::string);
std::string find_timezone(std::string const&);