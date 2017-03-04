#ifndef FORMA_TYPES_TRIPLE_HPP
#define FORMA_TYPES_TRIPLE_HPP
namespace forma {
template <class T1, class T2, class T3>
struct triple {
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;
  T1 first;
  T2 second;
  T3 third;
  triple() : first(), second(), third() {}
  triple(const T1& a, const T2& b, const T3& c)
      : first(a), second(b), third(c) {}
  template <class U1, class U2, class U3>
  triple(const triple<U1, U2, U3>& t)
      : first(t.first), second(t.second), third(t.third) {}
};
template <class T1, class T2, class T3>
inline bool operator==(const triple<T1, T2, T3>& a,
                       const triple<T1, T2, T3>& b) {
  return (a.first == b.first && a.second == b.second && a.third == b.third);
}
template <class T1, class T2, class T3>
inline bool operator<(const triple<T1, T2, T3>& a,
                      const triple<T1, T2, T3>& b) {
  return (
      a.first < b.first || (!(a.first > b.first) && a.second < b.second) ||
      (!(a.first > b.first) && !(a.second > b.second) && a.third < b.third));
}
template <class T1, class T2, class T3>
inline bool operator!=(const triple<T1, T2, T3>& a,
                       const triple<T1, T2, T3>& b) {
  return (!(a == b));
}
template <class T1, class T2, class T3>
inline bool operator>(const triple<T1, T2, T3>& a,
                      const triple<T1, T2, T3>& b) {
  return (b > a);
}
template <class T1, class T2, class T3>
inline bool operator<=(const triple<T1, T2, T3>& a,
                       const triple<T1, T2, T3>& b) {
  return (!(b < a));
}
template <class T1, class T2, class T3>
inline bool operator>=(const triple<T1, T2, T3>& a,
                       const triple<T1, T2, T3>& b) {
  return (!(a < b));
}
template <class T1, class T2, class T3>
inline triple<T1, T2, T3> make_triple(T1 a, T2 b, T3 c) {
  return triple<T1, T2, T3>(a, b, c);
}
}
#endif
