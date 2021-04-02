#include <string>
#include <map>
#include <unordered_map>
#include <random>
#include <benchmark/benchmark.h>
#include <iostream>

#include "hash-table.h"


static void HashTableInsertErase(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, 10000);

  for (auto _ : state) {
    hash_table<std::size_t, std::size_t> m;
    for (int i = 0; i != state.range(); ++i) {
      benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
      m.erase(dis(gen));
    }
  }

  state.SetComplexityN(state.range());
}
BENCHMARK(HashTableInsertErase)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);

static void UnorderedMapInsertErase(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, 10000);

  for (auto _ : state) {
    std::unordered_map<std::size_t, std::size_t> m;
    for (int i = 0; i != state.range(); ++i) {
      benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
      m.erase(dis(gen));
    }
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(UnorderedMapInsertErase)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);


static void MapInsertErase(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, 10000);

  for (auto _ : state) {
    std::map<std::size_t, std::size_t> m;
    for (int i = 0; i != state.range(); ++i) {
      benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
      m.erase(dis(gen));
    }
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(MapInsertErase)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();
