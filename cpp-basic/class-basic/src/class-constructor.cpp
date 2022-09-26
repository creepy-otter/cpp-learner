#include <iostream>

class Vec {
  int _n;
  int* _buf;

 public:
  Vec(int n) : _n(n) {
    std::cout << "--{Constructor} Vec(int)" << std::endl;
    _buf = new int[_n];
    for (int i = 0; i < _n; i++) {
      _buf[i] = 0;
    }
  }

  // Call copy constructor implicitly is not allowed by "explicit".
  explicit Vec(const Vec& v) {
    std::cout << "--{Copy Constructor} Vec(const Vec&)" << std::endl;
    _n = v._n;
    _buf = new int[_n];
    std::copy(v._buf, v._buf + v._n, _buf);
  }

  // Refer to: https://en.cppreference.com/w/cpp/language/operators
  Vec& operator=(const Vec& v) {
    std::cout << "--{Copy Assignment} Vec&(const Vec&)" << std::endl;
    // Guard self assignment
    if (this == &v) {
      return *this;
    }
    // Check if resource in *this could be reused.
    if (_n != v._n) {
      delete[] _buf;
      _buf = nullptr;
      _n = 0;
      // Preserve invariants in case next line throws
      _buf = new int[v._n];
      _n = v._n;
    }
    std::copy(v._buf, v._buf + v._n, _buf);
    return *this;
  }

  ~Vec() {
    std::cout << "--{Destructor} ~Vec()" << std::endl;
    if (_buf != nullptr) {
      delete[] _buf;
      _buf = nullptr;
    }
  }
};

void passByValue(Vec v) {
  // impl ...
}

// Return by value will call copy constructor implicitly without RVO (Return
// Value Optimization). RVO is forced by C++17, so we can try C++14 with
// flag -fno-elide-constructors to see the error.

// Vec returnByValue(int n) { return Vec(n); }

int main() {
  Vec v1(3);
  Vec v2(v1);

  // v3 won't be constructed because copy constructor is explicit.
  // Vec v3 = v1;

  // Pass by value will call copy constructor implicitly.
  // passByValue(v1);

  // returnByValue(3);

  return 0;
}