#include <benchmark/benchmark.h>

#include "alghoritms/algo1.h"

std::map<std::string, int> make_test_data() {
  std::map<std::string, int> result;
  for (int i = 0; i != 1000; ++i) {
    result[std::to_string(i) + "_aaa"] = (i % 4) - 2;
  }
  return result;
}

static void Algo1Old(benchmark::State &state) {
  auto test_data = make_test_data();
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo1_old(test_data, state.range()));
  }
}
BENCHMARK(Algo1Old)->Arg(10)->Arg(100)->Arg(1000);

static void Algo1New(benchmark::State &state) {
  auto test_data = make_test_data();
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo1_new(test_data, state.range()));
  }
}
BENCHMARK(Algo1New)->Arg(10)->Arg(100)->Arg(1000);

BENCHMARK_MAIN();
