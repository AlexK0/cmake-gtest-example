#include <benchmark/benchmark.h>
#include <random>
#include <limits>

//#include "alghoritms/algo4.h"

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


std::string algo4_new_1(const std::string &s) {
  std::string r = s;
  for (char &c : r) {
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9')) {
      //
    } else {
      c = '_';
    }
  }
  return r;
}

std::string algo4_new_2(const std::string &s) {
  std::string r = s;
  for (char &c : r) {
    c = std::isalnum(c) ? c : '_';
  }
  return r;
}

template<class F>
auto make_char_map(const F &mapper) {
  std::array<char, 256> char_map;
  for(size_t c = 0; c != char_map.size(); ++c){
    char_map[c] = mapper(static_cast<char>(c));
  }
  return char_map;
}

std::string algo4_new_3(const std::string &s) {
  const static auto char_map = make_char_map([](char c) {
    return std::isalnum(c) ? c : '_';
  });
  std::string r = s;
  for (char &c : r) {
    c = static_cast<char>(char_map[c]);
  }
  return r;
}


//
//static void Algo4Old(benchmark::State &state) {
//  auto test_data = make_test_data(state.range());
//  for (auto _ : state) {
//    benchmark::DoNotOptimize(algo4_old(test_data));
//  }
//  state.SetComplexityN(state.range(0));
//}
//BENCHMARK(Algo4Old)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo4New1(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo4_new_1(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo4New1)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo4New2(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo4_new_2(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo4New2)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

static void Algo4New3(benchmark::State &state) {
  auto test_data = make_test_data(state.range());
  for (auto _ : state) {
    benchmark::DoNotOptimize(algo4_new_3(test_data));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Algo4New3)->RangeMultiplier(2)->Range(1024, 256*1024)->Complexity()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
