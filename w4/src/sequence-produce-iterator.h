#pragma once

#include <iterator>

template<class T>
class SequenceProduceIterator {
public:
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using iterator_category = std::input_iterator_tag;

  SequenceProduceIterator() = default;
  SequenceProduceIterator(const T &start, const T &delta, size_t sequence_len) :
          state_{start},
          delta_{delta},
          left_{sequence_len} {}

  value_type operator*() { return state_; }

  // pre-increment: ++it
  SequenceProduceIterator &operator++() {
    state_ += delta_;
    --left_;
    return *this;
  }

  // post-increment: it++
  SequenceProduceIterator operator++(int) {
    SequenceProduceIterator old = *this;
    ++(*this);
    return old;
  }

  bool operator!=(const SequenceProduceIterator &other) const { return left_ != other.left_; }

private:
  T state_;
  T delta_;
  size_t left_{0};
};