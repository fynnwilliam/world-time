#pragma once

#include <string_view>

class status {
private:
  int code_ {}
  std::string_view message_;

public:
  status() = default;
  status(int i) : code_{i} {}
  status(std::string_view m) : message_{std::move(m)} {}
  status(int i, std::string_view m) : code_{i}, message_{std::move(m)} {}

  operator bool() const noexcept {
    std::cout << message;
    return code_ == 0;
  }
};
