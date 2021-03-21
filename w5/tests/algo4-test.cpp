#include "alghoritms/algo4.h"

#include <gtest/gtest.h>

std::string algo4_proxy(const std::string &s) {
  return algo4_old(s);
}

TEST(algo4_tests, test) {
  ASSERT_EQ(algo4_proxy("hello world 12 /*- lol \n ss"), std::string("hello_world_12_____lol___ss"));
}
