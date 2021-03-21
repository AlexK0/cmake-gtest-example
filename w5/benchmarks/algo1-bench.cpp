#include <benchmark/benchmark.h>

#include "alghoritms/algo1.h"

std::map<std::string, int> make_test_data(size_t elements) {
  std::map<std::string, int> result;
  for (size_t i = 0; i != elements; ++i) {
    result[std::to_string(i) + "_aaa"] = (i % 4) - 2;
  }
  return result;
}

static void Algo1Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo1_old(test_data, 517));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo1Old)->RangeMultiplier(2)->Range(512, 512*2*2*2*2*2)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo1New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo1_new(test_data, 517));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo1New)->RangeMultiplier(2)->Range(512, 512*2*2*2*2*2)->Complexity()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
