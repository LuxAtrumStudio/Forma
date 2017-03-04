#ifndef FORMA_TYPES_QUAD_HPP
#define FORMA_TYPES_QUAD_HPP
namespace forma {
template <class T1, class T2, class T3, class T4>
struct quad {
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;
  typedef T4 forth_type;
  T1 first;
  T2 second;
  T3 third;
  T4 forth;
  quad() : first(), second(), third(), forth() {}
  quad(const T1& a, const T2& b, const T3& c, const T4& d)
      : first(a), second(b), third(c), forth(d) {}
  template <class U1, class U2, class U3, class U4>
  quad(const quad<U1, U2, U3, U4>& t)
      : first(t.first), second(t.second), third(t.third), forth(t.forth) {}
};
template <class T1, class T2, class T3, class T4>
inline bool operator==(const quad<T1, T2, T3, T4>& a,
                       const quad<T1, T2, T3, T4>& b) {
  return (a.first == b.first && a.second == b.second && a.third == b.third &&
          a.forth == b.forth);
}
template <class T1, class T2, class T3, class T4>
inline bool operator<(const quad<T1, T2, T3, T4>& a,
                      const quad<T1, T2, T3, T4>& b) {
  return (
      a.first < b.first || (!(a.first > b.first) && a.second < b.second) ||
      (!(a.first > b.first) && !(a.second > b.second) && a.third < b.third) ||
      (!(a.first > b.first) && !(a.second > b.second) && !(a.third > b.third) &&
       a.forth < b.forth));
}
template <class T1, class T2, class T3, class T4>
inline bool operator!=(const quad<T1, T2, T3, T4>& a,
                       const quad<T1, T2, T3, T4>& b) {
  return (!(a == b));
}
template <class T1, class T2, class T3, class T4>
inline bool operator>(const quad<T1, T2, T3, T4>& a,
                      const quad<T1, T2, T3, T4>& b) {
  return (b > a);
}
template <class T1, class T2, class T3, class T4>
inline bool operator<=(const quad<T1, T2, T3, T4>& a,
                       const quad<T1, T2, T3, T4>& b) {
  return (!(b < a));
}
template <class T1, class T2, class T3, class T4>
inline bool operator>=(const quad<T1, T2, T3, T4>& a,
                       const quad<T1, T2, T3, T4>& b) {
  return (!(a < b));
}
template <class T1, class T2, class T3, class T4>
inline quad<T1, T2, T3, T4> make_quad(T1 a, T2 b, T3 c, T4 d) {
  return quad<T1, T2, T3, T4>(a, b, c, d);
}
}
#endif
