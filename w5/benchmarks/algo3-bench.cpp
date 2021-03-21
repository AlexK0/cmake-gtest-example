#include <benchmark/benchmark.h>
#include <random>

#include "alghoritms/algo3.h"

std::vector<int> make_test_data(size_t elements) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<int> dis(-100, 100);

  std::vector<int> result;
  result.reserve(elements);
  for (size_t i = 0; i != elements; ++i) {
    result.emplace_back(dis(gen));
  }
  return result;
}

static void Algo3Old(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    algo3_old(copy_data);
    benchmark::DoNotOptimize(copy_data);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo3Old)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo3New(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    algo3_new(copy_data);
    benchmark::DoNotOptimize(copy_data);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo3New)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo3New2(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    state.PauseTiming();
    auto copy_data = test_data;
    state.ResumeTiming();
    algo3_new2(copy_data);
    benchmark::DoNotOptimize(copy_data);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo3New2)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
