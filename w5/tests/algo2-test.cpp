#include "alghoritms/algo2.h"

#include <gtest/gtest.h>

int algo2_proxy(std::vector<double> &v, double x, double y) {
  return static_cast<int>(algo2_new(v, x, y));
}

TEST(algo2_tests, test) {
  std::vector<double> v{1, 2, 3, 4, 5, 6, 7, 9};
  std::vector<double> expected{3, 4, 5};
  ASSERT_EQ(algo2_proxy(v, 2.5, 5.1), 5);
  ASSERT_EQ(v, expected);
}
