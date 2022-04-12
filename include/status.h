#pragma once

#include <iostream>
#include <string>

namespace world_time {
class status {
private:
  int code_{};
  std::string message_;

public:
  status() = default;
  status(int i) : code_{i} {}
  status(std::string m) : message_{std::move(m)} {}
  status(int i, std::string m) : code_{i}, message_{std::move(m)} {}

  auto message() const noexcept { std::cout << message_; }

  operator bool() const noexcept {
    message();
    return code_ == 0;
  }
};
} // namespace world_time
