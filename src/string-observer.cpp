// string-observer.cpp
#include "string-observer.h"

std::ostream &operator<<(std::ostream &out, StringObserver::StringStat self) {
  return out << "[+" << self.added << ", "
             << "-" << self.removed << ", "
             << "=" << static_cast<int64_t>(self.added) - static_cast<int64_t>(self.removed) << "]";
}

std::ostream &operator<<(std::ostream &out, const StringObserver &self) {
  StringObserver::StringStat total;
  for (const auto &[str, counter] : self.counters_) {
    total.added += counter.added;
    total.removed += counter.removed;
    out << "'" << str << "': " << counter << std::endl;
  }
  return out << "total: " << total << std::endl;
}

