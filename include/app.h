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

  bool private_a(std::string const &) const;
  bool private_b(std::string const &) const;
  bool private_c(std::string const &) const;
  bool private_ip(std::string const &) const;
  bool public_ip(std::string const &) const;
  bool ip_address(std::string const &) const;
  std::string datetime();
  std::string capitalize(std::string);
  std::string to_lower(std::string);
  std::string ip(int, char **) const;
  std::string location(char **) noexcept;
  std::string find_timezone();
  std::string preposition() const;
  std::string usr_input() const;
  void _transform(std::string &, int);
  auto time(std::string const &);
  auto abbreviation(std::string const &);
  auto date(std::string const &);
  void check_arguments(int, char **);
  void update_url();
  void fetch_time();
  void display_time();
  auto invalid_argc() const;
  auto not_avaliable() const;

public:
  app(int i, char **c) : argc_{i}, argv_{c} {}
  void tell(int, char **);
};
