#include <numeric>
#include <cinttypes>

#include "algo5.h"


double algo5_old(const std::vector<int> &vs) {
  if (vs.empty()) {
    return 0;
  }
  int r = 0;
  for (int i = 0; i < vs.size(); i += 1) {
    r += vs[i];
  }
  return static_cast<double>(r) / static_cast<double>(vs.size());
}

double algo5_new(const std::vector<int> &vs) {
  return vs.empty() ? 0 : static_cast<double>(std::accumulate(vs.begin(), vs.end(), 0)) /
                          static_cast<double>(vs.size());
}

double algo5_new2(const std::vector<int> &vs) {
  if (vs.empty()) {
    return 0;
  }
  int64_t sum = 0;
  for (size_t i = 0; i != vs.size(); ++i) {
    sum += vs[i];
  }
  return static_cast<double>(sum) / static_cast<double>(vs.size());
}