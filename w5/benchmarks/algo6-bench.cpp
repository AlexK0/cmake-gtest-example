#include <benchmark/benchmark.h>
#include <random>

#include "alghoritms/algo6.h"

std::vector<std::vector<float>> make_test_data(size_t days, size_t measurements) {
  std::mt19937 gen{100500};
  std::uniform_real_distribution<float> dis(-100, 100);

  std::vector<std::vector<float>> result{days};
  for (auto &d : result) {
    d.assign(measurements, 0);
    for (auto &v : d) {
      v = dis(gen);
    }
  }
  return result;
}

static void Algo6Old(benchmark::State &state) {
  auto test_data = make_test_data(7, state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(ComputeAvgTemp(test_data));
  }
}
BENCHMARK(Algo6Old)->Arg(32*1024*1024);

static void Algo6New(benchmark::State &state) {
  auto test_data = make_test_data(7, state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(ComputeAvgTempNew(test_data));
  }
}
BENCHMARK(Algo6New)->Arg(32*1024*1024);

BENCHMARK_MAIN();
