#include <benchmark/benchmark.h>
#include <random>
#include <limits>

#include "alghoritms/algo4.h"

std::string make_test_data(size_t elements) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<char> dis(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());

  std::string result;
  result.reserve(elements);
  for (size_t i = 0; i != elements; ++i) {
    result.push_back(dis(gen));
  }
  return result;
}

static void Algo4Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo4_old(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo4Old)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity();

static void Algo4New2(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo4_new2(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo4New2)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity();

static void Algo4New3(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo4_new3(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo4New3)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity();

BENCHMARK_MAIN();
