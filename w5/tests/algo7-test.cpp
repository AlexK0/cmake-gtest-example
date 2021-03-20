#include "alghoritms/algo7.h"

#include <gtest/gtest.h>

std::vector<double> algo7_proxy(const std::vector<double> &s) {
  return algo7_old(s);
}

TEST(algo7_tests, test) {
  std::vector<double> v{10, 4, 6, 2, 1, 5, 3, 6, 9, 2};
  std::vector<double> expected{1, 5, 6, 10, 10, 10};
  ASSERT_EQ(algo7_proxy(v), expected);
}
