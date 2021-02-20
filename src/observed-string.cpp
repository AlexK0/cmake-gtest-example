// observed-string.cpp

#include "observed-string.h"

StringObserver &ObservedString::get_observer() noexcept {
  static StringObserver observer;
  return observer;
}
