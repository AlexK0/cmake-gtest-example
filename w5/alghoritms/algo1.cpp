#include <vector>
#include <map>
#include <algorithm>

#include "algo1.h"

std::vector<std::string> algo1_old(const std::map<std::string, int> &t, int x) {
  std::vector<std::string> r;
  if (t.empty()) {
    return r;
  }
  if (!x) {
    return r;
  }
  for (std::map<std::string, int>::const_iterator i = t.begin(); i != t.end(); i++) {
    if (i->second < 0) {
      r.push_back(i->first);
    }
  }

  std::vector<std::string> r2;
  for (int i = 0; i < r.size(); i = i + 1) {
    r2.insert(r2.begin(), r[i]);
  }

  while(r2.size() > x) {
    r2.pop_back();
  }

  return r2;
}

std::vector<std::string> algo1_new(const std::map<std::string, int> &table, size_t limit) noexcept {
  std::vector<std::string> result;
  result.reserve(std::min(limit, table.size()));
  for (auto it = table.rbegin(); it != table.rend() && limit; ++it) {
    if (it->second < 0) {
      result.emplace_back(it->first);
      --limit;
    }
  }
  return result;
}
