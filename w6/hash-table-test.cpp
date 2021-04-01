#include "hash-table.h"

#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <random>

using namespace std::string_literals;

TEST(hash_table_tests, test_empty_hash_table) {
  hash_table<std::string, int> table;

  ASSERT_TRUE(table.empty());
  ASSERT_EQ(table.size(), std::size_t{0});

  ASSERT_EQ(table.count("xxx"), std::size_t{0});
  ASSERT_EQ(table.find("yyy"), nullptr);
  ASSERT_EQ(table.erase("zzzz"), std::size_t{0});
}

TEST(hash_table_tests, test_insert) {
  hash_table<std::string, std::string> table;
  using vt = hash_table<std::string, std::string>::value_type;

  table["hello"] = "world";
  ASSERT_EQ(table["hello"], "world"s);

  table["aaaa"] = "bbbb";
  ASSERT_EQ(table["aaaa"], "bbbb"s);

  ASSERT_EQ(table.count("hello"), std::size_t{1});
  ASSERT_EQ(*table.find("hello"), vt("hello"s, "world"s));

  table["xyz"] = "qweweqweqwe";
  ASSERT_EQ(table["xyz"], "qweweqweqwe"s);

  for (int i = 0; i < 500; ++i) {
    table[std::to_string(i) + "_key"] = std::to_string(i) + "_value";
    ASSERT_EQ(table[std::to_string(i) + "_key"], std::to_string(i) + "_value");
  }

  ASSERT_EQ(table.size(), 503);
}

TEST(hash_table_tests, test_erase) {
  struct SameHash {
    std::size_t operator()(std::size_t v) const {
      return v;
    }
  };

  hash_table<std::size_t, std::string, SameHash> table;

  table[1] = "1";
  ASSERT_EQ(table[1], "1"s);

  table[1 + 17] = "1 + 17";
  ASSERT_EQ(table[1 + 17], "1 + 17"s);

  table[1 + 17 * 2] = "1 + 17 * 2";
  ASSERT_EQ(table[1 + 17 * 2], "1 + 17 * 2"s);

  table[2] = "2";
  ASSERT_EQ(table[2], "2"s);

  table[1 + 17 * 3] = "1 + 17 * 3";
  ASSERT_EQ(table[1 + 17 * 3], "1 + 17 * 3"s);

  table[2 + 17] = "2 + 17";
  ASSERT_EQ(table[2 + 17], "2 + 17"s);

  table[3] = "3";
  ASSERT_EQ(table[3], "3"s);

  ASSERT_EQ(table.size(), 7);

  table.erase(1);

  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table[1 + 17], "1 + 17"s);
  ASSERT_EQ(table[1 + 17 * 2], "1 + 17 * 2"s);
  ASSERT_EQ(table[2], "2"s);
  ASSERT_EQ(table[1 + 17 * 3], "1 + 17 * 3"s);
  ASSERT_EQ(table[2 + 17], "2 + 17"s);
  ASSERT_EQ(table[3], "3"s);
  ASSERT_EQ(table.size(), 6);

  table.erase(1 + 17);
  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table.find(1 + 17), nullptr);
  ASSERT_EQ(table[1 + 17 * 2], "1 + 17 * 2"s);
  ASSERT_EQ(table[2], "2"s);
  ASSERT_EQ(table[1 + 17 * 3], "1 + 17 * 3"s);
  ASSERT_EQ(table[2 + 17], "2 + 17"s);
  ASSERT_EQ(table[3], "3"s);
  ASSERT_EQ(table.size(), 5);

  table.erase(1 + 17 * 2);
  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table.find(1 + 17), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 2), nullptr);
  ASSERT_EQ(table[2], "2"s);
  ASSERT_EQ(table[1 + 17 * 3], "1 + 17 * 3"s);
  ASSERT_EQ(table[2 + 17], "2 + 17"s);
  ASSERT_EQ(table[3], "3"s);
  ASSERT_EQ(table.size(), 4);

  table.erase(2);
  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table.find(1 + 17), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 2), nullptr);
  ASSERT_EQ(table.find(2), nullptr);
  ASSERT_EQ(table[1 + 17 * 3], "1 + 17 * 3"s);
  ASSERT_EQ(table[2 + 17], "2 + 17"s);
  ASSERT_EQ(table[3], "3"s);
  ASSERT_EQ(table.size(), 3);

  table.erase(1 + 17 * 3);
  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table.find(1 + 17), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 2), nullptr);
  ASSERT_EQ(table.find(2), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 3), nullptr);
  ASSERT_EQ(table[2 + 17], "2 + 17"s);
  ASSERT_EQ(table[3], "3"s);
  ASSERT_EQ(table.size(), 2);

  table.erase(2 + 17);
  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table.find(1 + 17), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 2), nullptr);
  ASSERT_EQ(table.find(2), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 3), nullptr);
  ASSERT_EQ(table.find(2 + 17), nullptr);
  ASSERT_EQ(table[3], "3"s);
  ASSERT_EQ(table.size(), 1);

  table.erase(3);
  ASSERT_EQ(table.find(1), nullptr);
  ASSERT_EQ(table.find(1 + 17), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 2), nullptr);
  ASSERT_EQ(table.find(2), nullptr);
  ASSERT_EQ(table.find(1 + 17 * 3), nullptr);
  ASSERT_EQ(table.find(2 + 17), nullptr);
  ASSERT_EQ(table.find(3), nullptr);
  ASSERT_EQ(table.size(), 0);
}

TEST(hash_table_tests, test_under_load) {
  hash_table<std::size_t, std::string> table;
  std::unordered_map<std::size_t, std::string> stl_table;

  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, 50000);

  for (size_t i = 0; i != 1000000; ++i) {
    std::string v = std::to_string(i);
    std::size_t key = dis(gen);
    table[key] = v;
    stl_table[key] = std::move(v);

    if (dis(gen) < 20000) {
      key = dis(gen);
      ASSERT_EQ(stl_table.erase(key), table.erase(key));
    }

    key = dis(gen);
    ASSERT_EQ(stl_table.count(key), table.count(key));

    if (dis(gen) == 0) {
      stl_table.clear();
      table.clear();
    }
  }

  ASSERT_EQ(stl_table.size(), table.size());
  for (const auto &kv : stl_table) {
    auto *kv_table = table.find(kv.first);
    ASSERT_NE(kv_table, nullptr);
    ASSERT_EQ(*kv_table, kv);
  }
}