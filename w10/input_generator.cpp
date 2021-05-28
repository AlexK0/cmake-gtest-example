#include <iostream>
#include <fstream>
#include <string_view>
#include <vector>
#include <random>
#include <unordered_set>
#include <ctime>
#include <algorithm>

std::string gen_random_string(std::mt19937_64 &rand_gen, size_t max_len_size,
                              std::string_view edge_chars, std::string_view inner_chars) noexcept {
  std::uniform_int_distribution<size_t> distribution{1, max_len_size};
  std::string random_string(distribution(rand_gen), '\0');

  distribution.param(std::uniform_int_distribution<size_t>::param_type{size_t{0}, edge_chars.size() - 1});
  random_string.front() = edge_chars[distribution(rand_gen)];
  random_string.back() = edge_chars[distribution(rand_gen)];

  distribution.param(std::uniform_int_distribution<size_t>::param_type{size_t{0}, inner_chars.size() - 1});
  for (size_t i = 1; i + 1 < random_string.size(); ++i) {
    random_string[i] = inner_chars[distribution(rand_gen)];
  }
  return random_string;
}

std::vector<std::string> gen_random_strings(std::mt19937_64 &rand_gen, size_t elements, size_t max_len_size,
                                            std::string_view edge_chars, std::string_view inner_chars) {
  std::vector<std::string> result;
  result.reserve(elements);
  std::unordered_set<std::string_view> unique_random_strings{elements};
  while (unique_random_strings.size() != elements) {
    result.emplace_back(gen_random_string(rand_gen, max_len_size, edge_chars, inner_chars));
    if (!unique_random_strings.emplace(result.back()).second) {
      result.pop_back();
    }
  }
  return result;
}

int gen_input(std::ostream &out, size_t buses_count, size_t stops_count, size_t route_size, size_t request_count) {
  constexpr std::string_view edge_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdfghijklmnopqrstuvwxyz123456789"};
  constexpr std::string_view inner_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdfghijklmnopqrstuvwxyz123456789 "};
  std::mt19937_64 rand_gen{static_cast<size_t>(std::time(nullptr))};

  auto buses = gen_random_strings(rand_gen, buses_count, 20, edge_chars, inner_chars);
  const auto stops = gen_random_strings(rand_gen, stops_count, 20, edge_chars, inner_chars);

  std::uniform_real_distribution<double> coordinate{1, 2};
  std::uniform_int_distribution<size_t> route_selector{0, 1};
  std::uniform_int_distribution<size_t> stop_selector{0, stops.size() - 1};
  std::uniform_int_distribution<size_t> rout_size_selector{0, route_size};

  out << buses_count + stops_count << std::endl;
  while (buses_count || stops_count) {
    std::uniform_int_distribution<size_t> distribution{0, buses_count + stops_count - 1};
    if (stops_count && distribution(rand_gen) >= buses_count) {
      out << "Stop " << stops[--stops_count] << ": " << coordinate(rand_gen) << ", " << coordinate(rand_gen)
          << std::endl;
    } else {
      out << "Bus " << buses[--buses_count] << ": ";
      const char route_type = ">-"[route_selector(rand_gen)];
      const std::string_view first_stop = stops[stop_selector(rand_gen)];
      out << first_stop;
      const size_t route_size_rand = rout_size_selector(rand_gen);
      for (size_t i = 1; i + 1 < route_size_rand; ++i) {
        out << " " << route_type << " " << stops[stop_selector(rand_gen)];
      }
      out << " " << route_type << " " << (route_type == '>' ? first_stop : stops[stop_selector(rand_gen)]) << std::endl;
    }
  }

  if (request_count > buses.size()) {
    buses.reserve(request_count);
    while (buses.size() != request_count) {
      buses.emplace_back(gen_random_string(rand_gen, 20, edge_chars, inner_chars));
    }
  }
  std::shuffle(buses.begin(), buses.end(), rand_gen);
  buses.resize(request_count);

  out << request_count << std::endl;
  for (const auto &bus : buses) {
    out << "Bus " << bus << std::endl;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    std::cerr << "Not enough params" << std::endl;
    return 1;
  }
  const size_t buses_count = std::stoul(argv[1]);
  const size_t stops_count = std::stoul(argv[2]);
  const size_t route_size = std::stoul(argv[3]);
  const size_t request_count = std::stoul(argv[4]);

  if (argc > 5) {
    std::ofstream input_file{argv[5]};
    return gen_input(input_file, buses_count, stops_count, route_size, request_count);
  }
  return gen_input(std::cout, buses_count, stops_count, route_size, request_count);
}