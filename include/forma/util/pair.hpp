#ifndef FORMA_UTIL_PAIR_HPP_
#define FORMA_UTIL_PAIR_HPP_

namespace forma {
  template <typename _T>
  struct Pair {
    union {
      _T x, w, a;
    };
    union {
      _T y, h, b;
    };
  };
}  // namespace forma

#endif  // FORMA_UTIL_PAIR_HPP_
