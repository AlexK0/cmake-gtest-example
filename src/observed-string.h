// observed-string.h

#pragma once

#include "string-observer.h"

#include <cstring>

class ObservedString {
public:
  ObservedString(const char *s, size_t len) : str_{s, len} {
    on_string_create();
  }

  explicit ObservedString(const char *s) : ObservedString(s, std::strlen(s)) {}

  ObservedString(const ObservedString &other) : ObservedString(other.c_str(), other.size()) {}

  ObservedString(ObservedString &&other) : str_{std::move(other.str_)} { other.str_.clear(); }

  ObservedString &operator=(const ObservedString &other);

  ObservedString &operator+=(const ObservedString &other);

  friend ObservedString operator+(const ObservedString &lhs, const ObservedString &rhs);

  const char *c_str() const noexcept { return str_.c_str(); }

  size_t size() const noexcept { return str_.size(); }

  ~ObservedString() { on_string_remove(); }

  static StringObserver &get_observer() noexcept;

private:
  void on_string_create() noexcept;
  void on_string_remove() noexcept;

  std::string str_;
};

