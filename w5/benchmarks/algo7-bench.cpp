#include <benchmark/benchmark.h>
#include <random>

#include "alghoritms/algo7.h"

std::vector<double> make_test_data(size_t elements) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<int> dis(-100, 10000);

  std::vector<double> result(elements);
  for (auto &d : result) {
    d = dis(gen);
  }
  return result;
}

static void Algo7Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo7_old(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo7Old)->RangeMultiplier(2)->Range(1024*1024, 16*1024*1024)->Complexity();

static void Algo7New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo7_new(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo7New)->RangeMultiplier(2)->Range(1024*1024, 16*1024*1024)->Complexity();


static void Algo7New2(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo7_new2(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo7New2)->RangeMultiplier(2)->Range(1024*1024, 16*1024*1024)->Complexity();

BENCHMARK_MAIN();
