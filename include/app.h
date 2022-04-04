#pragma once
#include <exception>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>

#include <curlpp/Exception.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

#include "timezns.h"

class app {
private:
  int argc_{};
  char **argv_;
  std::string usr_input_;
  std::string url_{"http://worldtimeapi.org/api"};
  std::stringstream fetched_;

  timezns timezns_;
  std::vector<std::string> const days_of_week_{
      "Sunday",   "Monday", "Tuesday", "Wednesday",
      "Thursday", "Friday", "Saturday"};
  std::vector<std::string> const months_{
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};

  bool private_a(std::string const &) const;
  bool private_b(std::string const &) const;
  bool private_c(std::string const &) const;
  bool private_ip(std::string const &) const;
  bool public_ip(std::string const &) const;
  bool ip_address(std::string const &) const;
  std::string datetime();
  std::string capitalize(std::string);
  std::string to_lower(std::string);
  std::string ip() const;
  std::string location();
  std::string find_timezone();
  std::string preposition() const;
  std::string usr_input() const;
  void _transform(std::string &, int);
  auto time(std::string const &);
  auto abbreviation(std::string const &);
  inline std::string _month(int m) const { return months_[m - 1]; }
  auto date(std::string const &);
  void check_arguments();
  void update_url();
  void fetch_time();
  void display_time();
  auto invalid_argc() const;
  auto not_avaliable() const;

public:
  app(int i, char **c) : argc_{i}, argv_{c} {}
  void tell();
};
