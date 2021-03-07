#pragma once

#include <vector>
#include <random>
#include <unordered_map>

template<class T>
class ShuffleAccessIterator {
public:
  ShuffleAccessIterator(std::vector<T> &target, size_t left, size_t total, std::random_device::result_type seed) noexcept:
          seed_{seed},
          random_gen_{seed_},
          distribution_{0, target.size() - 1},
          target_{&target},
          left_iterations_{left},
          total_iterations_{total} {
    random_gen_.discard(total_iterations_ - left_iterations_);
    if (left_iterations_) {
      next_ = distribution_(random_gen_);
    }
  }

  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using iterator_category = std::bidirectional_iterator_tag;

  reference operator*() noexcept { return (*target_)[next_]; }
  pointer operator->() noexcept { return &((*target_)[next_]); }

  bool operator==(const ShuffleAccessIterator &other) const {
    return left_iterations_ == other.left_iterations_ && total_iterations_ == other.total_iterations_ &&
            seed_ == other.seed_ && target_ == other.target_;
  }

  bool operator!=(const ShuffleAccessIterator &other) const {
    return !(*this == other);
  }

  ShuffleAccessIterator &operator++() noexcept {
    if (left_iterations_) {
      next_ = distribution_(random_gen_);
      --left_iterations_;
    } else {
      // undefined behaviour
    }
    return *this;
  }

  ShuffleAccessIterator &operator--() noexcept {
  if (left_iterations_ != total_iterations_) {
      random_gen_.seed(seed_);
      random_gen_.discard(total_iterations_ - left_iterations_ - 1);
      next_ = distribution_(random_gen_);
      ++left_iterations_;
    } else {
      // undefined behaviour
    }
    return *this;
  }

  ShuffleAccessIterator operator++(int) noexcept {
    ShuffleAccessIterator old = *this;
    ++(*this);
    return old;
  }

  ShuffleAccessIterator operator--(int) noexcept {
    ShuffleAccessIterator old = *this;
    --(*this);
    return old;
  }

private:
  std::random_device::result_type seed_{0};
  std::mt19937_64 random_gen_;
  std::uniform_int_distribution<size_t> distribution_;
  std::vector<T> *target_;
  size_t next_{0};
  size_t left_iterations_{0};
  size_t total_iterations_{0};
};

template<class T>
class ShuffleAccessRange {
public:
  ShuffleAccessRange(std::vector<T> &target, size_t elements) :
          seed_{std::random_device{}()},
          first_{target, elements, elements, seed_},
          last_{target, 0, elements, seed_} {}

  explicit ShuffleAccessRange(std::vector<T> &target) :
          ShuffleAccessRange{target, target.size()} {}

  auto begin() const { return first_; }
  auto end() const { return last_; }

  auto rbegin() const { return std::make_reverse_iterator(last_); }
  auto rend() const { return std::make_reverse_iterator(first_); }

private:
  std::random_device::result_type seed_{0};
  ShuffleAccessIterator<T> first_;
  ShuffleAccessIterator<T> last_;
};

