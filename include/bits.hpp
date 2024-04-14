#pragma once

#include <cstddef>

namespace bits {

// Return the number of bits in the given number of bytes.
constexpr std::size_t count(const std::size_t &n) noexcept {
  return n * __CHAR_BIT__;
}

// Return the number of bits in the type T.
template <typename T>
constexpr std::size_t len(T && = T{}) noexcept {
  return count(sizeof(T));
}

} // namespace bits
