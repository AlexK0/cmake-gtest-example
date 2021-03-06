#pragma once

#include <vector>
#include <random>

template<class T>
class ShuffleAccessIterator {
public:
  explicit ShuffleAccessIterator(std::vector<T> &target) noexcept:
          random_gen_{std::random_device{}()},
          distribution_{0, target.size() - 1},
          target_{target} {}

  using value_type = T;
  using difference_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = std::output_iterator_tag;

  value_type &operator*() noexcept {
    return target_[distribution_(random_gen_)];
  }

  // pre-increment: ++it
  ShuffleAccessIterator& operator++() noexcept {
    return *this;
  }

  // post-increment: it++
  ShuffleAccessIterator operator++(int) noexcept {
    ShuffleAccessIterator old = *this;
    ++(*this);
    return old;
  }

private:
  std::mt19937_64 random_gen_;
  std::uniform_int_distribution<size_t> distribution_;
  std::vector<T> &target_;
};