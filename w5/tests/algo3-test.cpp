#include "alghoritms/algo3.h"

#include <gtest/gtest.h>

void algo3_proxy(std::vector<int> &v) {
  algo3_new2(v);
  std::sort(v.begin(), v.end());
}

TEST(algo3_tests, test) {
  std::vector<int> v{5, 2, 6, 9, 4, 2, 1, 9, 4, 2, 2, 9, 1, 1, 5};
  std::vector<int> expected{1, 2, 4, 5, 6, 9};
  algo3_proxy(v);
  ASSERT_EQ(v, expected);
}
