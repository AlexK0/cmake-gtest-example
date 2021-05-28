#pragma once

#include <cassert>
#include <cstring>
#include <string_view>
#include <utility>

class my_str {
public:
  my_str() = default;

  my_str(const char *s, size_t size) :
          size_(size),
          capacity_(size) {
    if (size) {
      raw_str_ = new char[size + 1];
      std::memcpy(raw_str_, s, size);
    }
  }

  my_str(const my_str &other) :
          my_str(other.raw_str_, other.size_) {
  }

  my_str(my_str &&other) noexcept:
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)),
          raw_str_(std::exchange(other.raw_str_, nullptr)) {
  }

  my_str &operator=(const my_str &other) = delete;
  my_str &operator=(my_str &&other) = delete;

  const char *c_str() const noexcept { return raw_str_; }

  size_t size() const noexcept { return size_; }

  void push_back(char c) {
    if (size_ == capacity_) {
      capacity_ = std::max(size_t{2}, capacity_ * 2);
      char *new_str = new char[capacity_ + 1];
      std::memcpy(new_str, raw_str_, size_ + 1);
      delete[]raw_str_;
      raw_str_ = new_str;
    }
    raw_str_[size_++] = c;
    raw_str_[size_] = '\0';
  }

  void pop_back() {
    assert(size_);
    raw_str_[--size_] = '\0';
  }

private:
  size_t size_{0};
  size_t capacity_{0};
  char *raw_str_{nullptr};
};


class my_str2 {
public:
  my_str2() = default;

  my_str2(const char *s) :
          my_str2(s, std::strlen(s)) {
  }

  my_str2(const char *s, size_t size) :
          size_(size),
          str_({{'\0'}}) {
    if (use_heap()) {
      str_.heap_.raw_str_ = new char[size + 1];
      str_.heap_.capacity_ = size;
    }
    if (size_) {
      char *raw = get_raw();
      memcpy(raw, s, size);
      raw[size] = '\0';
    }
  }

  my_str2(const my_str &other) :
          my_str2(other.c_str(), other.size()) {
  }

  my_str2(my_str2 &&other) noexcept:
          size_(std::exchange(other.size_, 0)),
          str_(other.str_) {
    other.str_.static_[0] = '\0';
  }

  ~my_str2() {
    if (use_heap()) {
      delete[] str_.heap_.raw_str_;
    }
  }


  my_str2 &operator=(const my_str2 &other) = delete;
  my_str2 &operator=(my_str2 &&other) = delete;

  const char *c_str() const noexcept { return use_heap() ? str_.heap_.raw_str_ : str_.static_.data(); }

  size_t size() const noexcept { return size_; }

  void push_back(char c) {
    const size_t old_capacity = get_capacity();
    char *raw_str = get_raw();
    if (size_ == old_capacity) {
      const size_t new_capacity = old_capacity * 2;
      raw_str = new char[new_capacity + 1];
      std::memcpy(raw_str, c_str(), size_ + 1);
      if (use_heap()) {
        delete[] str_.heap_.raw_str_;
      }
      str_.heap_ = RawHeap_{raw_str, new_capacity};
    }
    raw_str[size_++] = c;
    raw_str[size_] = '\0';
  }

  void pop_back() {
    assert(size_);
    const bool use_heap_before = use_heap();
    char *raw_before = get_raw();
    raw_before[--size_] = '\0';
    if (use_heap_before && !use_heap()) {
      std::copy(raw_before, raw_before + size_ + 1, str_.static_.begin());
      delete[] raw_before;
    }
  }

private:
  bool use_heap() const noexcept {
    return size_ + 1 > sizeof(RawHeap_);
  }

  char *get_raw() noexcept {
    return use_heap() ? str_.heap_.raw_str_ : str_.static_.data();
  }

  size_t get_capacity() const noexcept {
    return use_heap() ? str_.heap_.capacity_ : (sizeof(RawHeap_) - 1);
  }

  size_t size_{0};

  struct RawHeap_ {
    char *raw_str_{nullptr};
    size_t capacity_{0};
  };

  union {
    std::array<char, sizeof(RawHeap_)> static_;
    RawHeap_ heap_;
  } str_{};
};