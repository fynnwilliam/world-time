#pragma once

#include <curlpp/Exception.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <exception>
#include <iostream>
#include <regex>

#include "status.h"
#include "timezns.h"

class app {
private:
  std::string usr_input_;
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
  status ip(char **);
  std::string find_timezone();
  std::string preposition() const;
  std::string usr_input() const;
  std::string _url();
  status fetch_time();
  status check_arguments(int, char **);
  status display_time();
  auto location(char **) noexcept;
  auto fetch(std::string const &);
  void _transform(std::string &, int);
  auto time(std::string const &);
  auto abbreviation(std::string const &);
  auto date(std::string const &);
  auto invalid(char **) const noexcept;
  auto zone_unavailable() const noexcept;

public:
  void tell(int, char **);
};
