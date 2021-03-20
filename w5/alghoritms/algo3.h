#pragma once

#include <algorithm>
#include <vector>
#include <unordered_set>

template<class T>
void algo3_old(std::vector<T> &v) {
  for (int i = 0; i < v.size(); i += 1) {
    for (int j = i + 1; j < v.size();) {
      if (v[i] == v[j]) {
        v.erase(v.begin() + j);
      } else {
        j = j + 1;
      }
    }
  }
}

template<class T>
void algo3_new(std::vector<T> &v) {
  std::sort(v.begin(), v.end());
  const auto last_it = std::unique(v.begin(), v.end());
  v.erase(last_it, v.end());
}

template<class T>
void algo3_new2(std::vector<T> &v) {
  std::unordered_set<T> table{v.begin(), v.end()};
  v.assign(table.begin(), table.end());
}
