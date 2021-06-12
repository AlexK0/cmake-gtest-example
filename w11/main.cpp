#include <iostream>

#include <string>
#include <string_view>
#include <unordered_set>
#include <forward_list>
#include <vector>
#include <variant>
#include <string>

namespace ex1 {
  class StringCache {
  public:
    bool add1(std::string str) {
      return cache_.emplace(std::move(str)).second;
    }

    bool add2(const std::string &str) {
      return cache_.emplace(std::move(str)).second;
    }

    bool add3(std::string &&str) {
      return cache_.emplace(std::move(str)).second;
    }

  private:
    std::unordered_set<std::string> cache_;
  };
} // ex1

int main() {
  ex1::StringCache s;
  s.add1("sss");
  s.add2("sss");
  s.add3("sss");

  return 0;
}
