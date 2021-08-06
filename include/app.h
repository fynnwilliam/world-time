#pragma once
#include <regex>
#include <vector>
#include <iostream>
#include <exception>
#include <unordered_map>

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
    std::string abbreviation_;
    std::string time_;
    std::string date_;
    std::string day_;
    std::stringstream fetched_;

    std::unordered_map<std::string, timezn> timezns_;
    std::vector<std::string> const days_of_week_{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::vector<std::string> const months_{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    bool private_a(std::string const&) const;
    bool private_b(std::string const&) const;
    bool private_c(std::string const&) const;
    bool private_ip(std::string const&) const;
    bool public_ip(std::string const&) const;
    bool ip_address(std::string const&) const;
    std::string datetime();
    std::string capitalize(std::string);
    std::string ip() const;
    std::string location();
    std::string find_timezone();
    std::string preposition() const;
    std::string _datetime() const;
    void time(std::string const&);
    void abbreviation(std::string const&);
    void day(std::string const&);
    inline std::string _day(int d) const { return days_of_week_[d]; }
    inline std::string _month(int m) const { return months_[m - 1]; }
    std::string month(std::string const&) const;
    void date(std::string const&);
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