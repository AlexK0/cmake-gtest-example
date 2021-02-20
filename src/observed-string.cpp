// observed-string.cpp

#include "observed-string.h"

StringObserver &ObservedString::get_observer() noexcept {
  static StringObserver observer;
  return observer;
}

ObservedString &ObservedString::operator=(const ObservedString &other) {
  get_observer().remove_string(str_);
  str_ = other.str_;
  get_observer().add_string(str_);
  return *this;
}

ObservedString &ObservedString::operator+=(const ObservedString &other) {
  get_observer().remove_string(str_);
  str_ += other.str_;
  get_observer().add_string(str_);
  return *this;
}

ObservedString operator+(const ObservedString &lhs, const ObservedString &rhs) {
  std::string tmp_str = lhs.str_ + rhs.str_;
  return ObservedString{tmp_str.c_str(), tmp_str.size()};
}

