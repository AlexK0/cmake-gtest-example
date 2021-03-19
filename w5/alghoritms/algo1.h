#pragma once

#include <vector>
#include <map>

std::vector<std::string> algo1_old(const std::map<std::string, int> &t, int x);
std::vector<std::string> algo1_new(const std::map<std::string, int> &table, size_t limit) noexcept;
