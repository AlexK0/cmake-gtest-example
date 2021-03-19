#include <benchmark/benchmark.h>

#include "alghoritms/algo2.h"

std::vector<double> make_test_data(size_t elements) {
  std::vector<double> result;
  result.reserve(elements);
  for (size_t i = 0; i != elements; ++i) {
    result.emplace_back(static_cast<double>(i) * 0.41);
  }
  return result;
}

static void Algo2Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    benchmark::DoNotOptimize(algo2_old(copy_data, 10, 50));
  }
}
BENCHMARK(Algo2Old)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000);

static void Algo2New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    benchmark::DoNotOptimize(algo2_new(copy_data, 10, 50));
  }
}
BENCHMARK(Algo2New)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_MAIN();
