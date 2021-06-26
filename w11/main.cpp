#include <iostream>

#include <string>
#include <string_view>
#include <unordered_set>
#include <forward_list>
#include <vector>
#include <variant>
#include <string>
#include <memory>

namespace ex1 {
  std::string trim(const std::string &s, char c) {
    std::string result;
    const size_t first = s.find_first_not_of(c);
    if (first != std::string::npos) {
      const size_t last = s.find_last_not_of(c);
      result = s.substr(first, (last - first + 1));
    }
    return result;
  }

  class StringCache {
  public:
    bool trim_and_add(std::string str) {
      std::string trimmed_str = std::move(trim(std::move(str), ' '));
      return cache_.emplace(std::move(trimmed_str)).second;
    }

    template<class S>
    bool add(S &&str) {
      return cache_.emplace(std::forward<S>(str)).second;
    }

  private:
    std::unordered_set<std::string> cache_;
  };
} // ex1

namespace ex2 {
  class StringCache {
  public:
    bool add(const std::string &s) {
      if (cache_.find(s) != cache_.end()) {
        return false;
      }
      elements_.emplace_back(std::make_unique<std::string>(s));
      return cache_.emplace(*elements_.back()).second;
    }

  private:
    std::vector<std::unique_ptr<std::string>> elements_;
    std::unordered_set<std::string_view> cache_;
  };

  class JsonObject {
  public:
    static std::unique_ptr<JsonObject> make_json(const std::string &raw_json) {
      return std::make_unique<JsonObject>(raw_json);
    }

  private:
    friend std::unique_ptr<JsonObject> std::make_unique<JsonObject>(const std::string &raw_json);

    explicit JsonObject(const std::string &) {}
  };


  size_t get_size_if_alive(const std::weak_ptr<std::string> &weak_str) {
    if (auto shared_str = weak_str.lock()) {
      return shared_str->size();
    }
    return 0;
  }
}

int main() {
  std::shared_ptr<int> x2{new int{10}}; // 2 аллокации памяти
  std::shared_ptr<int> x1{std::make_shared<int>(10)}; // 1 аллокация памяти
  return 0;
}
