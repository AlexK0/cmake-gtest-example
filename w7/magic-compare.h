#pragma once

#include <string>

bool magic_compare(const std::string &lhs, const std::string &rhs, const std::string &delimiters) noexcept;
bool magic_compare_new(const std::string &lhs, const std::string &rhs, const std::string &delimiters) noexcept;