#include <algorithm>
#include <array>

#include "algo4.h"

std::string algo4_old(const std::string &s) {
  if (s.empty()) {
    return {};
  }

  std::string r;
  std::string u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string l = "abcdefghijklmnopqrstuvwxyz";
  std::string d = "0123456789";

  for (int i = 0; i < s.size(); i = i + 1) {
    for (int j = 0; j < u.size(); j++) {
      if (u[j] == s[i]) {
        r.push_back(u[j]);
        continue;
      }
    }
    for (int j = 0; j < l.size(); j++) {
      if (l[j] == s[i]) {
        r.push_back(l[j]);
        continue;
      }
    }
    for (int j = 0; j < d.size(); j++) {
      if (d[j] == s[i]) {
        r.push_back(d[j]);
        continue;
      }
    }
    if (r.size() == i) {
      r.push_back('_');
    }
  }

  return r;
}

std::string algo4_new(const std::string &s) {
  std::string r;
  r.reserve(s.size());
  for (auto c : s) {
    r.push_back(std::isalnum(c) ? c : '_');
  }
  return r;
}

template<class F>
auto make_char_map(const F &transform) noexcept {
  std::array<char, 256> result;
  for (size_t c = 0; c != 256; ++c) {
    result[c] = transform(static_cast<char>(c));
  }
  return result;
}

std::string algo4_new2(const std::string &s) {
  static const auto char_map = make_char_map([](char c) { return std::isalnum(c) ? c : '_'; });
  std::string r;
  r.reserve(s.size());
  for (auto c : s) {
    r.push_back(static_cast<char>(char_map[c]));
  }
  return r;
}

template<class F>
auto make_char_transformer(const F &transform) noexcept {
  std::array<char, 256> char_map;
  for (size_t c = 0; c != 256; ++c) {
    char_map[c] = transform(static_cast<char>(c));
  }
  return [char_map](char &c) { c = static_cast<char>(char_map[c]); };
}

std::string algo4_new3(const std::string &s) {
  static const auto transformer = make_char_transformer([](char c) { return std::isalnum(c) ? c : '_'; });
  std::string result = s;
  std::for_each(result.begin(), result.end(), transformer);
  return result;
}