#include <string>
#include <map>
#include <unordered_map>
#include <random>
#include <benchmark/benchmark.h>

#include "hash-table.h"


static void HashTableFindInsert(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, state.range());

  for (auto _ : state) {
    hash_table<std::size_t, std::size_t> m(2 * state.range());
    for (int i = 0; i != state.range(); ++i) {
      if (dis(gen) % 4 == 0) {
        benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
      }
      benchmark::DoNotOptimize(m.find(dis(gen)));
    }
  }

  state.SetComplexityN(state.range());
}

BENCHMARK(HashTableFindInsert)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);

static void UnorderedMapFindInsert(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, state.range());

  for (auto _ : state) {
    std::unordered_map<std::size_t, std::size_t> m(2 * state.range());
    for (int i = 0; i != state.range(); ++i) {
      if (dis(gen) % 4 == 0) {
        benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
      }
      benchmark::DoNotOptimize(m.find(dis(gen)));
    }
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(UnorderedMapFindInsert)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);


static void MapFindInsert(benchmark::State &state) {
  std::mt19937 gen{100500};
  std::uniform_int_distribution<std::size_t> dis(0, state.range());

  for (auto _ : state) {
    std::map<std::size_t, std::size_t> m;
    for (int i = 0; i != state.range(); ++i) {
      if (dis(gen) % 4 == 0) {
        benchmark::DoNotOptimize(m.insert({dis(gen), 123}));
      }
      benchmark::DoNotOptimize(m.find(dis(gen)));
    }
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(MapFindInsert)->RangeMultiplier(2)->Range(2 << 15, 2 << 23)->Complexity()->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();
