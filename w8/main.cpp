#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <future>

class Profiler {
public:
  explicit Profiler(const char *name) :
          name_(name),
          start_(std::chrono::steady_clock::now()) {
  }

  ~Profiler() noexcept {
    const auto dur = std::chrono::steady_clock::now() - start_;
    std::cout << std::fixed << std::setprecision(4)
              << std::chrono::duration<double>{dur}.count() << "s [" << name_ << "]" << std::endl;
  }

private:
  const char *name_;
  std::chrono::steady_clock::time_point start_;

};

template<class T>
void stl_algo_unique(std::vector<T> &data) {
  std::sort(data.begin(), data.end());
  data.erase(std::unique(data.begin(), data.end()), data.end());
}

template<class T>
void unordered_set_unique(std::vector<T> &data) {
  std::unordered_set<T> unique_data{std::make_move_iterator(data.begin()), std::make_move_iterator(data.end())};
  data.assign(std::make_move_iterator(unique_data.begin()), std::make_move_iterator(unique_data.end()));
}

template<class T>
void unordered_set_unique_threads(std::vector<T> &data, size_t threads_count) {
  std::vector<std::future<std::unordered_set<T>>> results;
  results.reserve(threads_count);

  const size_t interval = data.size() / threads_count;
  size_t tail_size = data.size() - interval * threads_count;
  auto first = data.begin();

  for (size_t i = 0; i != threads_count; ++i) {
    auto last = first + interval;
    if (tail_size) {
      --tail_size;
      ++last;
    }

    results.emplace_back(std::async( [first, last] {
      return std::unordered_set<T>{std::make_move_iterator(first), std::make_move_iterator(last)};
    }));
    first = last;
  }

  std::unordered_set<T> unique_data;
  for (size_t i = 0; i != threads_count; ++i) {
    std::unordered_set<T> thread_unique_data = results[i].get();
    if (unique_data.empty()) {
      unique_data = std::move(thread_unique_data);
    } else {
      unique_data.insert(std::make_move_iterator(thread_unique_data.begin()), std::make_move_iterator(thread_unique_data.end()));
    }
  }
  data.assign(std::make_move_iterator(unique_data.begin()), std::make_move_iterator(unique_data.end()));
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    return 1;
  }

  int elements = std::atoi(argv[1]);
  int range = std::atoi(argv[2]);
  std::vector<int> data0(elements);
  for (int &n : data0) {
    n = std::rand() % range;
  }

  std::vector<int> data1 = data0;
  std::vector<int> data2 = data0;

  {
    Profiler p{"stl_algo_unique"};
    stl_algo_unique(data0);
  }

  std::unique_lock

  {
    Profiler p{"unordered_set_unique"};
    unordered_set_unique(data1);
  }

  {
    Profiler p{"unordered_set_unique_threads"};
    unordered_set_unique_threads(data2, 8);
  }

  std::sort(data1.begin(), data1.end());
  std::sort(data2.begin(), data2.end());
  assert(data0 == data1);
  assert(data0 == data2);

  return 0;
}