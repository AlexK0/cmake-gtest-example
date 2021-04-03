#include <string>
#include <map>
#include <unordered_map>
#include <random>
#include <benchmark/benchmark.h>

#include "hash-table.h"


static void HashTableInsert(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, state.range());

  for (auto _ : state) {
    hash_table<std::size_t, std::size_t> m(2*state.range());
    for (int i = 0; i != state.range(); ++i) {
      benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
    }
  }

  state.SetComplexityN(state.range());
}
BENCHMARK(HashTableInsert)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);

static void UnorderedMapInsert(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, state.range());

  for (auto _ : state) {
    std::unordered_map<std::size_t, std::size_t> m(2*state.range());
    for (int i = 0; i != state.range(); ++i) {
      benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
    }
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(UnorderedMapInsert)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);


static void MapInsert(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, state.range());

  for (auto _ : state) {
    std::map<std::size_t, std::size_t> m;
    for (int i = 0; i != state.range(); ++i) {
      benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
    }
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(MapInsert)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();
