#include "alghoritms/algo5.h"

#include <gtest/gtest.h>

double algo5_proxy(const std::vector<int> &s) {
  return algo5_old(s);
}

TEST(algo5_tests, test) {
  std::vector<int> v{1, 1, -1, 2, -3, 5, 2};
  ASSERT_DOUBLE_EQ(algo5_proxy(v), 1);
}
