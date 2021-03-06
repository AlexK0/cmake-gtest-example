#pragma once

#include <vector>
#include <random>

template<class T>
class ShuffleAccessIterator {
public:
  ShuffleAccessIterator(std::vector<T> &target, size_t left) noexcept:
          random_gen_{std::random_device{}()}, distribution_{0, target.size() - 1},
          target_{target}, left_(left), next_{distribution_(random_gen_)} {}

  explicit ShuffleAccessIterator(std::vector<T> &target) noexcept: ShuffleAccessIterator{target, target.size()} {}

  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using iterator_category = std::forward_iterator_tag;

  reference operator*() noexcept { return target_[next_]; }

  pointer operator->() noexcept { return &target_[next_]; }

  bool operator!=(const ShuffleAccessIterator &other) const {
    if (left_ == other.left_ && left_ == 0) {
      return &target_ != &other.target_;
    }
    return left_ != other.left_ || random_gen_ != other.random_gen_ || &target_ != &other.target_;
  }

  // pre-increment: ++it
  ShuffleAccessIterator &operator++() noexcept {
    next_ = distribution_(random_gen_);
    --left_;
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
  size_t next_{0};
  size_t left_{0};
};

template<class T>
class ShuffleAccessRange {
public:
  ShuffleAccessRange(std::vector<T> &target, size_t elements) :
          first_{target, elements},
          last_{target, 0} {}

  explicit ShuffleAccessRange(std::vector<T> &target) :
          ShuffleAccessRange{target, target.size()} {}

  auto begin() const { return first_; }
  auto end() const { return last_; }

private:
  ShuffleAccessIterator<T> first_;
  ShuffleAccessIterator<T> last_;
};