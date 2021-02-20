// string-observer.h
#pragma once

#include <string>
#include <ostream>
#include <unordered_map>


class StringObserver {
public:
  void add_string(const std::string &s) { ++counters_[s].added; }

  void remove_string(const std::string &s) { ++counters_[s].removed; };

  friend std::ostream &operator<<(std::ostream &out, const StringObserver &self);

private:
  struct StringStat {
    size_t added{0};
    size_t removed{0};
  };

  friend std::ostream &operator<<(std::ostream &out, StringStat self);

  std::unordered_map<std::string, StringStat> counters_;
};

