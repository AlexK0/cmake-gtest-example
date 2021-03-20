#include "alghoritms/algo6.h"

#include <gtest/gtest.h>

std::vector<float> algo6_proxy(const std::vector<std::vector<float>> &s) {
  return ComputeAvgTempNew(s);
}

TEST(algo6_tests, test) {
  std::vector<std::vector<float>> v;
  v.emplace_back(std::vector<float>{1, 1,-1, 2,-3,-5});
  v.emplace_back(std::vector<float>{7, 3, 1, 4, 1,-6});
  v.emplace_back(std::vector<float>{0,-3, 4, 0, 1, 4});
  std::vector<float> expected{4, 2, 2.5, 3, 1, 4};
  ASSERT_EQ(algo6_proxy(v), expected);
}
