#pragma once
#include <regex>
#include <vector>
#include <iostream>
#include <exception>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "timezn.h"

class app
{
private:
    int argc_{};
    char** argv_;
    std::string usr_input_;
    std::string url_{"http://worldtimeapi.org/api"};
    std::stringstream fetched_;
    
    std::vector<timezn> timezns_;
    std::vector<std::string> const week_days{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::vector<std::string> const months{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    bool private_a(std::string const&) const;
    bool private_b(std::string const&) const;
    bool private_c(std::string const&) const;
    bool private_ip(std::string const&) const;
    bool public_ip(std::string const&) const;
    bool ip_address(std::string const&) const;
    std::string datetime();
    std::string to_lower(std::string);
    std::string ip() const;
    std::string location() const;
    std::string find_timezone();
    std::string time(std::string const&) const;
    std::string abbreviation(std::string const&) const;
    std::string day(std::string const&) const;
    inline std::string _day(int d) const { return week_days[d]; }
    inline std::string _month(int m) const { return months[m - 1]; }
    std::string month(std::string const&) const;
    std::string date(std::string const&) const;
    void read_timezones();
    void check_arguments();
    void update_url();
    void api_call();
    void display_time();
    auto invalid_argc() const;
    auto not_avaliable() const;
    
public:
    app(int i, char** c) : argc_{i}, argv_{c} {}
    void tell();
};