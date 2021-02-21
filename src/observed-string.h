// observed-string.h

#pragma once

#include "string-observer.h"

#include <cstring>
#include <iostream>

class ObservedString {
public:
  ObservedString(const char *s, size_t len) : str_{s, len} {
    std::cout << "ctr: " << str_ << std::endl;
    on_string_create();
  }

  explicit ObservedString(const char *s) : ObservedString(s, std::strlen(s)) {}

  ObservedString(const ObservedString &other) : str_(other.str_) {
    std::cout << "copy ctr: " << str_ << std::endl;
    on_string_create();
  }
  ObservedString(ObservedString &&other);

  ObservedString &operator=(const ObservedString &other);
  ObservedString &operator=(ObservedString &&other);

  ObservedString &operator+=(const ObservedString &other);

  friend ObservedString operator+(const ObservedString &lhs, const ObservedString &rhs);

  const char *c_str() const noexcept { return str_.c_str(); }

  size_t size() const noexcept { return str_.size(); }

  ~ObservedString() {
    std::cout << "~dctr: " << str_ << std::endl;
    on_string_remove();
  }

  static StringObserver &get_observer() noexcept;

private:
  void on_string_create() noexcept;
  void on_string_remove() noexcept;

  std::string str_;
};

