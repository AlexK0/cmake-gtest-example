#include <cinttypes>

#include "algo6.h"

std::vector<float> ComputeAvgTemp(const std::vector<std::vector<float>>& vs) {
  int m = vs.size();
  if (vs.empty()) return {};
  int n = vs[0].size();

  std::vector<float> results(n);
  std::vector<float> sums(n, 0.f);
  std::vector<int> counts(n, 0);

  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      float c = vs[j][i];
      sums[i] += (c > 0 ? c : 0.f);
      counts[i] += (c > 0 ? 1 : 0);
    }
  }

  for (int i = 0; i < n; ++i) {
    results[i] = counts[i] == 0 ? 0 : sums[i] / counts[i];
  }

  return results;
}

std::vector<float> ComputeAvgTempNew(const std::vector<std::vector<float>>& vs) {
  if (vs.empty()) {
    return {};
  }

  const size_t n = vs[0].size();
  std::vector<float> results(n, 0.f);
  std::vector<uint32_t> counts(n, 0);
  for (const auto &day : vs) {
    for (size_t i = 0; i != n; ++i) {
      const float c = day[i];
      results[i] += (c > 0 ? c : 0.f);
      counts[i] += (c > 0 ? 1 : 0);
    }
  }

  for (size_t i = 0; i != n; ++i) {
    results[i] = counts[i] == 0 ? 0 : (results[i] / counts[i]);
  }

  return results;
}
