#include <iostream>

// template <typename T>
// std::ostream& myprint(std::ostream& os, const T& t) {
//   return os << t << std::endl;
// }

// template <typename T, typename... Args>
// std::ostream& myprint(std::ostream& os, const T& t, const Args&... args) {
//   os << t << ", ";
//   return myprint(os, args...);
// }

template <typename... Args>
int getArgsSize(const Args&... args) {
  return sizeof...(args);
}

template <typename... Args>
std::ostream& myprint(std::ostream& os, const Args&... args) {
  // fold expression.
  // is equivalent to ((((os << 1) << 2 ) << 3) << 4) << 5)
  return (os << ... << args);
}

int main() {
  std::cout << getArgsSize(1, 2, 3, 4, 5) << std::endl;
  myprint(std::cout, 1, 2, 3, 4, 5);
  return 0;
}