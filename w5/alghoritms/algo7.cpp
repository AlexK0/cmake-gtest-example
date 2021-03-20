#include <set>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <array>

#include "algo7.h"

std::vector<double> algo7_old(const std::vector<double> &v) {
  if (v.empty()) {
    return {};
  }

  std::multiset<double> s;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] >= 0) {
      s.insert(v[i]);
    }
  }

  if (s.empty()) {
    return {};
  }

  return {
          *std::next(s.begin(), 0 * s.size() / 100),
          *std::next(s.begin(), 50 * s.size() / 100),
          *std::next(s.begin(), 75 * s.size() / 100),
          *std::next(s.begin(), 95 * s.size() / 100),
          *std::next(s.begin(), 99 * s.size() / 100),
          *std::next(s.begin(), 100 * s.size() / 100),
  };
}

std::vector<double> algo7_new(const std::vector<double> &v) {
  std::vector<double> sorted;
  std::copy_if(v.begin(), v.end(), std::back_inserter(sorted), [](double c) { return c >= 0; });
  std::sort(sorted.begin(), sorted.end());
  if (sorted.empty()) {
    return {};
  }
  std::vector<double> result{0, 50, 75, 95, 99};
  for (auto &p : result) {
    p = sorted[static_cast<size_t>(p * sorted.size() / 100)];
  }
  result.emplace_back(sorted.back());
  return result;
}

double get_percentile(std::vector<double> &copy, size_t percentile) {
  const size_t index = percentile * copy.size() / 100;
  std::nth_element(copy.begin(), copy.end(), copy.begin() + index);
  return copy[index];
}

std::vector<double> algo7_new2(const std::vector<double> &v) {
  std::vector<double> copy;
  std::copy_if(v.begin(), v.end(), std::back_inserter(copy), [](double c) { return c >= 0; });
  if (copy.empty()) {
    return {};
  }
  return copy.empty()
         ? std::vector<double>{}
         : std::vector<double>{
                  *std::min_element(copy.begin(), copy.end()),
                  get_percentile(copy, 50),
                  get_percentile(copy, 75),
                  get_percentile(copy, 95),
                  get_percentile(copy, 99),
                  *std::max_element(copy.begin(), copy.end()),
          };
}
