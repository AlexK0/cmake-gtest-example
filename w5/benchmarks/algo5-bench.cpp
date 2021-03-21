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

static void Algo5Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo5_old(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo5Old)->RangeMultiplier(2)->Range(128*1024, 1024*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo5New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo5_new(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo5New)->RangeMultiplier(2)->Range(128*1024, 1024*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo5New2(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo5_new2(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo5New2)->RangeMultiplier(2)->Range(128*1024, 1024*1024)->Complexity()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
