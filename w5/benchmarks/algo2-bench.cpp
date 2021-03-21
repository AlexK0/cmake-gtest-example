#include <random>
#include <benchmark/benchmark.h>

#include "alghoritms/algo2.h"

std::vector<double> make_test_data(size_t elements) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<int> dis(-100, 100);

  std::vector<double> result;
  result.reserve(elements);
  for (size_t i = 0; i != elements; ++i) {
    result.emplace_back(dis(gen));
  }
  return result;
}

static void Algo2Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    benchmark::DoNotOptimize(algo2_old(copy_data, 0, 100));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo2Old)->RangeMultiplier(2)->Range(1024, 1024*2*2*2*2*2)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo2New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    benchmark::DoNotOptimize(algo2_new(copy_data, 0, 100));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo2New)->RangeMultiplier(2)->Range(1024, 1024*2*2*2*2*2)->Complexity()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
