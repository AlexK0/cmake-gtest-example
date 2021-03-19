#include "alghoritms/algo1.h"

#include <gtest/gtest.h>

std::vector<std::string> algo1_proxy(const std::map<std::string, int> &t, int x) {
  return algo1_new(t, x);
}

TEST(algo1_tests, test) {
  std::map<std::string, int> table;
  table["aaaa"] = 1;
  table["bbb"] = -1;
  table["ccc"] = -5;
  table["dddd"] = -7;
  table["eeee"] = 4;
  table["ffff"] = -4;
  table["ggggg"] = -1;

  std::vector<std::string> expected{"ggggg", "ffff", "dddd"};
  ASSERT_EQ(algo1_proxy(table, 3), expected);
}
