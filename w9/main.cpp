#include <iostream>

#include <string>
#include <string_view>
#include <unordered_set>
#include <forward_list>
#include <vector>
#include <variant>

#include "my-str.h"

class StringCache {
public:
  std::vector<std::string_view> cached_split(std::string &&str) {
    auto words = split_into_words(str);
    bool save_string = false;
    for (auto &word : words) {
      auto [it, was_inserted] = cache_.insert(word);
      if (!was_inserted) {
        word = *it;
      } else {
        save_string = true;
      }
    }
    if (save_string) {
      raw_strings_.emplace_front(std::move(str));
    }
    return words;
  }

private:
  static std::vector<std::string_view> split_into_words(std::string_view str) {
    std::vector<std::string_view> result;
    while (true) {
      const auto space = str.find(' ');
      const auto word = str.substr(0, space);
      if (!word.empty()) {
        result.push_back(word);
      }
      if (space == str.npos) {
        break;
      } else {
        str.remove_prefix(space + 1);
      }
    }
    return result;
  }

  std::unordered_set<std::string_view> cache_;
  std::forward_list<std::string> raw_strings_;
};

int main() {
  my_str2 s1{"hello"};

  assert(!strcmp(s1.c_str(), "hello"));
  assert(s1.size() == 5);

  my_str2 s2 = std::move(s1);
  assert(!strcmp(s1.c_str(), ""));
  assert(s1.size() == 0);
  assert(!strcmp(s2.c_str(), "hello"));
  assert(s2.size() == 5);

  my_str2 s3{"hello world foo bar"};
  assert(!strcmp(s3.c_str(), "hello world foo bar"));
  assert(s3.size() == 19);
  const char *old_ptr = s3.c_str();

  s3.pop_back();
  assert(s3.c_str() == old_ptr);

  s3.pop_back();
  assert(s3.c_str() == old_ptr);

  s3.pop_back();
  assert(s3.c_str() == old_ptr);

  s3.pop_back();
  assert(s3.c_str() != old_ptr);

  assert(!strcmp(s3.c_str(), "hello world foo"));
  assert(s3.size() == 15);

  old_ptr = s3.c_str();

  s3.push_back('a');
  assert(!strcmp(s3.c_str(), "hello world fooa"));
  assert(s3.size() == 16);
  assert(s3.c_str() != old_ptr);

  my_str2 s4 = std::move(s3);
  assert(!strcmp(s3.c_str(), ""));
  assert(s3.size() == 0);

  assert(!strcmp(s4.c_str(), "hello world fooa"));
  assert(s4.size() == 16);

  StringCache c;

  assert(c.cached_split("hello world") == (std::vector<std::string_view>{"hello", "world"}));
  assert(c.cached_split("hello world aaa bbb ccc") ==
         (std::vector<std::string_view>{"hello", "world", "aaa", "bbb", "ccc"}));

  return 0;
}
