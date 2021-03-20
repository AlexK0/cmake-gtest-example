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
    benchmark::DoNotOptimize(algo1_old(test_data, 277));
  }
}
BENCHMARK(Algo1Old)->Arg(128)->Arg(128*2)->Arg(128*2*2)->Arg(128*2*2*2);

static void Algo1New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo1_new(test_data, 277));
  }
}
BENCHMARK(Algo1New)->Arg(128)->Arg(128*2)->Arg(128*2*2)->Arg(128*2*2*2);

BENCHMARK_MAIN();
