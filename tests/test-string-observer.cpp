// test-string-observer.cpp
#include "string-observer.h"

#include <gtest/gtest.h>
#include <sstream>

std::string as_string(const StringObserver &string_observer) {
  std::ostringstream oss;
  oss << string_observer;
  return oss.str();
}

TEST(string_observer_tests, test_empty) {
  StringObserver string_observer;
  ASSERT_EQ(as_string(string_observer), "total: [+0, -0, =0]\n");
}

TEST(string_observer_tests, test_adding) {
  StringObserver string_observer;
  string_observer.add_string("hello");
  string_observer.add_string("world");
  string_observer.add_string("hello");

  std::string str_report = as_string(string_observer);
  ASSERT_NE(str_report.find("'hello': [+2, -0, =2]\n"), std::string::npos);
  ASSERT_NE(str_report.find("'world': [+1, -0, =1]\n"), std::string::npos);
  ASSERT_NE(str_report.find("total: [+3, -0, =3]\n"), std::string::npos);
}

TEST(string_observer_tests, test_removing) {
  StringObserver string_observer;
  string_observer.add_string("world");
  string_observer.add_string("hello");
  string_observer.add_string("world");
  string_observer.remove_string("world");
  string_observer.remove_string("hello");

  std::string str_report = as_string(string_observer);
  ASSERT_NE(str_report.find("'hello': [+1, -1, =0]\n"), std::string::npos);
  ASSERT_NE(str_report.find("'world': [+2, -1, =1]\n"), std::string::npos);
  ASSERT_NE(str_report.find("total: [+3, -2, =1]\n"), std::string::npos);
}
