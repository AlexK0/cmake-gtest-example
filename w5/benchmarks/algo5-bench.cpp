#include <benchmark/benchmark.h>
#include <random>

#include "alghoritms/algo5.h"

std::vector<int> make_test_data(size_t elements) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<int> dis(-100, 100);

  std::vector<int> result(elements);
  for (auto &d : result) {
    d = dis(gen);
  }
  return result;
}

static void Algo6Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo5_old(test_data));
  }
}
BENCHMARK(Algo6Old)->RangeMultiplier(2)->Range(64*1024, 512*1024);

static void Algo6New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo5_new2(test_data));
  }
}
BENCHMARK(Algo6New)->RangeMultiplier(2)->Range(64*1024, 512*1024);

BENCHMARK_MAIN();
