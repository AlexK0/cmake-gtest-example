#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <deque>

class ThreadPool {
public:
  explicit ThreadPool(size_t threads_count) {
    threads_.reserve(threads_count);
    for (size_t thread_id = 0; thread_id != threads_count; ++thread_id) {
      threads_.emplace_back([this] { main_loop(); });
    }
  }

  ~ThreadPool() {
    stop_ = true;
    new_task_event_.notify_all();
    for (auto &t : threads_) {
      t.join();
    }
  }

  template<class F>
  auto execute(F &&user_task) {
    using RetType = decltype(user_task());
    if constexpr(std::is_same<RetType, void>{}) {
      enqueue(Task{std::forward<F>(user_task)});
    } else {
      struct Context {
        explicit Context(std::decay_t<F> t) : user_task(std::move(t)) {}

        std::promise<RetType> user_task_promise;
        F user_task;
      };

      auto ctx = std::make_shared<Context>(std::forward<F>(user_task));
      auto user_future = ctx->user_task_promise.get_future();
      enqueue([ctx = std::move(ctx)]() mutable {
        try {
          ctx->user_task_promise.set_value(ctx->user_task());
        } catch (...) {
          try {
            ctx->user_task_promise.set_exception(std::current_exception());
          } catch (...) {
            assert(0);
          }
        }
      });
      return user_future;
    }
  }

private:
  using Task = std::function<void()>;

  void main_loop() {
    while (!stop_) {
      if (Task task = get_task()) {
        task();
      }
    }
  }

  Task get_task() {
    Task task;
    std::unique_lock<std::mutex> l{queue_mutex_};
    new_task_event_.wait(l, [this] { return stop_ || !task_queue_.empty(); });
    if (!task_queue_.empty()) {
      task = std::move(task_queue_.front());
      task_queue_.pop_front();
    }
    return task;
  }

  void enqueue(Task &&task) {
    {
      std::lock_guard<std::mutex> l{queue_mutex_};
      task_queue_.emplace_back(std::move(task));
    }
    new_task_event_.notify_one();
  }

  std::atomic<bool> stop_{false};
  std::vector<std::thread> threads_;

  std::condition_variable new_task_event_;
  std::mutex queue_mutex_;
  std::deque<Task> task_queue_;
};