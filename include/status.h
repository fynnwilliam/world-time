#pragma once

class status_code {
private:
  int code_ {}

public:
  status_code() = default;
  status_code(int i) : code_{i} {}

  operator bool() const noexcept { return code_ == 0; }
};
