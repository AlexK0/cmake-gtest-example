#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cassert>
#include <random>
#include <future>


#include "thread_pool.h"

class Profiler {
public:
  explicit Profiler(const char *name) noexcept:
          name_(name),
          start_(std::chrono::steady_clock::now()) {
  }

  ~Profiler() noexcept {
    const auto t = std::chrono::steady_clock::now() - start_;
    std::cout << std::fixed << std::setprecision(2)
              << std::chrono::duration<double>{t}.count() << "s [" << name_ << "]" << std::endl;
  }

private:
  const char *name_;
  const std::chrono::steady_clock::time_point start_;
};

template<class T>
void algo_unique(std::vector<T> &data) {
  std::sort(data.begin(), data.end());
  data.erase(std::unique(data.begin(), data.end()), data.end());
}

template<class T>
void unordered_set_unique(std::vector<T> &data) {
  std::unordered_set<T> unique_data{std::make_move_iterator(data.begin()), std::make_move_iterator(data.end())};
  data.assign(std::make_move_iterator(unique_data.begin()), std::make_move_iterator(unique_data.end()));
}

template<class T>
void unordered_set_parallel_unique(std::vector<T> &data, size_t threads_count) {
  std::vector<std::thread> threads;
  threads.reserve(threads_count);
  std::vector<std::unordered_set<T>> thread_result{threads_count};

  const size_t bucket_size = data.size() / threads_count;
  size_t tail_size = data.size() - bucket_size * threads_count;
  auto first = data.begin();
  for (size_t i = 0; i != threads_count; ++i) {
    auto last = first + bucket_size;
    if (tail_size) {
      ++last;
      --tail_size;
    }

    threads.emplace_back([&thread_result, first, last, i] {
      thread_result[i] = {std::make_move_iterator(first), std::make_move_iterator(last)};
    });
    first = last;
  }

  std::unordered_set<T> result;
  for (size_t i = 0; i != threads_count; ++i) {
    threads[i].join();
    if (i == 0) {
      result = std::move(thread_result[i]);
    } else {
      for (auto &str : thread_result[i]) {
        result.emplace(std::move(str));
      }
    }
  }
  data.assign(std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));
}

template<class T>
void unordered_set_parallel_unique2(std::vector<T> &data, size_t threads_count) {
  std::vector<std::thread> threads;
  threads.reserve(threads_count);

  std::vector<std::future<std::unordered_set<T>>> thread_results;
  thread_results.reserve(threads_count);

  const size_t bucket_size = data.size() / threads_count;
  size_t tail_size = data.size() - bucket_size * threads_count;
  auto first = data.begin();
  for (size_t i = 0; i != threads_count; ++i) {
    auto last = first + bucket_size;
    if (tail_size) {
      ++last;
      --tail_size;
    }

    std::promise<std::unordered_set<T>> thread_result_promise;
    thread_results.emplace_back(thread_result_promise.get_future());
    threads.emplace_back([thread_result = std::move(thread_result_promise), first, last] () mutable {
      thread_result.set_value(std::unordered_set<T>{std::make_move_iterator(first), std::make_move_iterator(last)});
    });
    first = last;
  }

  std::unordered_set<T> result;
  for (size_t i = 0; i != threads_count; ++i) {
    threads[i].join();
    if (i == 0) {
      result = thread_results[i].get();
    } else {
      for (auto &str : thread_results[i].get()) {
        result.emplace(std::move(str));
      }
    }
  }
  data.assign(std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));
}

template<class T>
void unordered_set_parallel_unique3(std::vector<T> &data, size_t threads_count) {
  std::vector<std::future<std::unordered_set<T>>> async_tasks;
  async_tasks.reserve(threads_count);

  const size_t bucket_size = data.size() / threads_count;
  size_t tail_size = data.size() - bucket_size * threads_count;
  auto first = data.begin();
  for (size_t i = 0; i != threads_count; ++i) {
    auto last = first + bucket_size;
    if (tail_size) {
      ++last;
      --tail_size;
    }

    async_tasks.emplace_back(std::async([first, last] {
      return std::unordered_set<T>{std::make_move_iterator(first), std::make_move_iterator(last)};
    }));
    first = last;
  }

  std::unordered_set<T> result;
  for (std::future<std::unordered_set<T>> &task_result : async_tasks) {
    if (result.empty()) {
      result = task_result.get();
    } else {
      for (auto &str : task_result.get()) {
        result.emplace(std::move(str));
      }
    }
  }
  data.assign(std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));
}

template<class T>
void unordered_set_parallel_unique4(std::vector<T> &data, ThreadPool &thread_pool, size_t threads_count) {
  std::vector<std::future<std::unordered_set<T>>> async_tasks;
  async_tasks.reserve(threads_count);

  const size_t bucket_size = data.size() / threads_count;
  size_t tail_size = data.size() - bucket_size * threads_count;
  auto first = data.begin();
  for (size_t i = 0; i != threads_count; ++i) {
    auto last = first + bucket_size;
    if (tail_size) {
      ++last;
      --tail_size;
    }

    async_tasks.emplace_back(thread_pool.execute([first, last] {
      return std::unordered_set<T>{std::make_move_iterator(first), std::make_move_iterator(last)};
    }));
    first = last;
  }

  std::unordered_set<T> result;
  for (std::future<std::unordered_set<T>> &task_result : async_tasks) {
    if (result.empty()) {
      result = task_result.get();
    } else {
      for (auto &str : task_result.get()) {
        result.emplace(std::move(str));
      }
    }
  }
  data.assign(std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    return 1;
  }

  const int range = std::atoi(argv[2]);
  std::vector<int> data(std::atoi(argv[1]));
  for(int &i : data) {
    i = std::rand() % range;
  }

  std::vector<int> data0 = data;
  std::vector<int> data1 = data;
  std::vector<int> data2 = data;
  std::vector<int> data3 = data;
  std::vector<int> data4 = std::move(data);

  {
    Profiler p{"algo_unique"};
    algo_unique(data0);
  }
  {
    Profiler p{"unordered_set_unique"};
    unordered_set_unique(data1);
  }
  {
    Profiler p{"unordered_set_parallel_unique"};
    unordered_set_parallel_unique(data2, 8);
  }
  {
    Profiler p{"unordered_set_parallel_unique3"};
    unordered_set_parallel_unique3(data3, 8);
  }
  ThreadPool pool{8};
  {
    Profiler p{"unordered_set_parallel_unique4"};
    unordered_set_parallel_unique4(data4, pool, 8);
  }

  std::sort(data1.begin(), data1.end());
  std::sort(data2.begin(), data2.end());
  std::sort(data3.begin(), data3.end());
  assert(data1 == data2);
  assert(data2 == data3);
  return 0;
}
