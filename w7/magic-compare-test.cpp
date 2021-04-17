#include "magic-compare.h"

#include <gtest/gtest.h>
#include <string>

TEST(magic_compare_test, test_magic_compare) {
  ASSERT_TRUE(magic_compare("hello world", "world hello", " "));
  ASSERT_TRUE(magic_compare("aa bb cc\tdd\nee aa\tbb", "aa cc bb ee dd", " \t\n"));
  ASSERT_TRUE(magic_compare("aa cc bb", "bb aa cc", " \t\n"));

  ASSERT_FALSE(magic_compare("aa bb cc\tdd\nee aa\tbb f", "aa cc bb ee dd", " \t\n"));
  ASSERT_FALSE(magic_compare("aa bb cc", "aa cc", " \t\n"));
  ASSERT_FALSE(magic_compare("aa cc", "bb aa cc", " \t\n"));



  ASSERT_TRUE(magic_compare_new("hello world   ", "world    hello", " "));
  ASSERT_TRUE(magic_compare_new("aa bb cc\tdd\nee aa\t\n\t bb", "aa cc bb ee dd\n", " \t\n"));
  ASSERT_TRUE(magic_compare_new("aa cc bb", "bb aa cc", " \t\n"));

  ASSERT_FALSE(magic_compare_new("aa bb cc\tdd\nee aa\tbb f", "aa cc bb ee dd", " \t\n"));
  ASSERT_FALSE(magic_compare_new("aa bb cc", "aa cc", " \t\n"));
  ASSERT_FALSE(magic_compare_new("aa cc", "bb aa cc", " \t\n"));
}