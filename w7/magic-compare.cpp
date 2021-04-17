#include <algorithm>
#include <vector>
#include <string_view>
#include <bitset>

#include "magic-compare.h"

namespace {

  std::vector<std::string> split(const std::string &str, const std::string &delimiters) {
    std::vector<std::string> result;
    std::string word;
    for (char c : str) {
      if (delimiters.find(c) == std::string::npos) {
        word.push_back(c);
      } else if (!word.empty()) {
        result.push_back(word);
        word = std::string{};
      }
    }
    if (!word.empty()) {
      result.push_back(word);
    }
    return result;
  }

  bool contains(const std::vector<std::string> &container, const std::string &word) noexcept {
    return std::find(container.begin(), container.end(), word) != container.end();
  }

} // namespace

bool magic_compare(const std::string &lhs, const std::string &rhs, const std::string &delimiters) noexcept {
  for (auto l_word : split(lhs, delimiters)) {
    if (!contains(split(rhs, delimiters), l_word)) {
      return false;
    }
  }

  for (auto r_word : split(rhs, delimiters)) {
    if (!contains(split(lhs, delimiters), r_word)) {
      return false;
    }
  }
  return true;
}

namespace {

  using char_set = std::bitset<std::numeric_limits<uint8_t>::max()>;

  template<class F>
  bool for_each_word(std::string_view str, const char_set &delimiters, const F &f) {
    size_t word_start = 0;
    for (size_t i = 0; i != str.size(); ++i) {
      if (delimiters.test(str[i])) {
        if (i != word_start) {
          if (!f(std::string_view{&str[word_start], i - word_start})) {
            return false;
          }
        }
        word_start = i + 1;
      }
    }
    if (word_start != str.size()) {
      return f(std::string_view{&str[word_start], str.size() - word_start});
    }
    return true;
  }

}

bool magic_compare_new(const std::string &lhs, const std::string &rhs, const std::string &delimiters) noexcept {
  char_set delimiters_set;
  for (auto c : delimiters) {
    delimiters_set.set(static_cast<uint8_t>(c));
  }

  std::string_view longest = lhs;
  std::string_view shortest = rhs;
  if (longest.size() < shortest.size()) {
    std::swap(longest, shortest);
  }

  std::unordered_map<std::string_view, std::bitset<2>> words;
  for_each_word(shortest, delimiters_set, [&words](std::string_view word) {
    words[word].set(0);
    return true;
  });

  if (!for_each_word(longest, delimiters_set, [&words](std::string_view word) {
    auto &mask = words[word];
    mask.set(1);
    return mask.all();
  })) {
    return false;
  }

  constexpr auto check_diff = [](const auto &word_mask) { return !word_mask.second.all(); };
  return std::find_if(words.begin(), words.end(), check_diff) == words.end();
}
