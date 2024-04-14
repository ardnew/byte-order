#pragma once

#include <cstdint>
#include <type_traits>

namespace bytes {

enum class ord: bool {
  msfirst       = false, // Most significant byte first (big-endian)
  lsfirst       = true,  // Least significant byte first (little-endian)

  // In my experience, datasheets specify byte significance more frequently than
  // the endianness; I usually get confused by the latter anyway.

  big_endian    = msfirst, // Use the *_endian aliases if more consistent with
  little_endian = lsfirst, // the rest of your docs/code.

  // "host" is the conventional name for the reverse of "network" byte order.
  // In particular, it is not equivalent to "native" — the compilation host.
  network       = msfirst,
  host          = lsfirst,

  // Most "native endianness" examples online either occur at runtime, are not
  // constexpr-compatible, or they mistakenly determine the endianness of the
  // compilation host.
  //
  // The following macro is defined by both gcc and clang, so it covers many of
  // the common cases (notably, MSVC and ICC are unverified.)
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  native        = msfirst,
  reverse       = lsfirst,
#elif   defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  native        = lsfirst,
  reverse       = msfirst,
#else
  #error "undefined: __BYTE_ORDER__ (of target architecture)"
#endif
};

template <typename V, ord To = ord::reverse, ord From = ord::native,
  typename U = typename std::make_unsigned<V>::type,
  typename std::enable_if_t<std::is_integral_v<V>>* = nullptr>
struct order {
private:
  static constexpr auto _size = sizeof(V);
  using byte_index = std::make_index_sequence<_size>;
  const V &_v;

  // byte swap unsigned integer of arbitrary size (1..N bytes)
  template <std::size_t ...N>
  inline static constexpr U swap(U v, std::index_sequence<N...>) noexcept {
    return ((((v>>bits::count(N)) & 0xFF) << bits::count(_size-1-N)) | ...);
  };

public:
  using type = U;

  order() = delete;
  inline constexpr order(const V &value): _v(value) {}

  ~order() = default;

  // Return the desired byte ordering by casting order to order::type.
  inline constexpr operator U() const noexcept {
    if constexpr (To == From) {
      return static_cast<U>(_v);
    } else {
      return swap(static_cast<U>(_v), byte_index{});
    }
  }
};

// Return the given integral value with a desired byte ordering.
//
// The returned value is unsigned and has the same size as the input value.
//
// The byte ordering is determined by template parameters `To` and `From`, which
// are platform-dependent ord::reverse and ord::native by default, respectively.
//
// This function is constexpr-compatible and is a convenience wrapper around the
// order struct.
template <ord To = ord::reverse, ord From = ord::native,
  typename V, typename O = order<V, To, From>>
inline constexpr auto reorder(const V &value) noexcept {
  return static_cast<typename O::type>(O(value));
}

} // namespace bytes
