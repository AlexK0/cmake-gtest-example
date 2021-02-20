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

