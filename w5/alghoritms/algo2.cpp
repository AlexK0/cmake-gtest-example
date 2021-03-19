#include <algorithm>

#include "algo2.h"

int algo2_old(std::vector<double> &v, double x, double y) {
  if (v.empty()) {
    return 0;
  }

  std::vector<int> i_s;
  for (int i = 0; i < v.size(); i = i + 1) {
    if (v[i] < x || v[i] > y) {
      i_s.emplace_back(i);
    }
  }

  if (i_s.empty()) {
    return 0;
  }

  int old_size = v.size();
  for (int i = i_s.size() - 1; i >= 0 ; i = i - 1) {
    v.erase(v.begin() + i_s[i]);
  }
  return old_size - v.size();
}

size_t algo2_new(std::vector<double> &v, double min, double max) noexcept {
  const auto last_it = std::remove_if(v.begin(), v.end(),
                                      [min, max](double x) {
                                        return x < min || x > max;
                                      });
  const size_t removed = static_cast<size_t>(v.end() - last_it);
  v.erase(last_it, v.end());
  return removed;
}
