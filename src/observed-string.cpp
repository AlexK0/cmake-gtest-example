// observed-string.cpp

#include "observed-string.h"

StringObserver &ObservedString::get_observer() noexcept {
  static StringObserver observer;
  return observer;
}

void ObservedString::on_string_create() noexcept {
  if (!str_.empty()) {
    get_observer().add_string(str_);
  }
}

void ObservedString::on_string_remove() noexcept {
  if (!str_.empty()) {
    get_observer().remove_string(str_);
  }
}

ObservedString::ObservedString(ObservedString &&other) {
  str_.swap(other.str_);
  other.str_.clear();
}

ObservedString &ObservedString::operator=(const ObservedString &other) {
  on_string_remove();
  str_ = other.str_;
  on_string_create();
  return *this;
}

ObservedString &ObservedString::operator=(ObservedString &&other) {
  on_string_remove();
  str_.swap(other.str_);
  other.str_.clear();
  return *this;
}

ObservedString &ObservedString::operator+=(const ObservedString &other) {
  on_string_remove();
  str_ += other.str_;
  on_string_create();
  return *this;
}

ObservedString operator+(const ObservedString &lhs, const ObservedString &rhs) {
  std::string tmp_str = lhs.str_ + rhs.str_;
  return ObservedString{tmp_str.c_str(), tmp_str.size()};
}

