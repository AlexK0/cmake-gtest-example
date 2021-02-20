// observed-string.h

#pragma once

#include "string-observer.h"

#include <cstring>

class ObservedString {
public:
  ObservedString(const char *s, size_t len) : str_{s, len} {
    get_observer().add_string(str_);
  }

  explicit ObservedString(const char *s) : ObservedString(s, std::strlen(s)) {}

  const char *c_str() const noexcept { return str_.c_str(); }

  size_t size() const noexcept { return str_.size(); }

  ~ObservedString() { get_observer().remove_string(str_); }

  static StringObserver &get_observer() noexcept;

private:
  std::string str_;
};

