#include <iostream>
#include <string>
class Vec {
  int _n;
  int *_buf;

public:
  Vec(int n) : _n(n) {
    std::cout << "Vec(int n)" << std::endl;
    _buf = new int[_n];
    for (int i = 0; i < _n; i++) {
      _buf[i] = 0;
    }
  }
  Vec(const Vec &v) {
    std::cout << "Vec(const Vec& v)" << std::endl;
    _n = v._n;
    _buf = new int[_n];
    for (int i = 0; i < _n; i++) {
      _buf[i] = 0;
    }
  }
  Vec(Vec &&v) {
    std::cout << "Vec(Vec&& v)" << std::endl;
    _n = v._n;
    _buf = v._buf;
    v._buf = nullptr;
  }
  friend Vec operator+(const Vec &a, const Vec &b) {
    std::cout << "friend Vec operator+ (const Vec& a, const Vec& b)"
              << std::endl;
    if (a._n != b._n) {
      std::cout << "Dimension not match!" << std::endl;
      exit(1);
    }
    Vec res(a._n);
    for (int i = 0; i < a._n; i++) {
      res._buf[i] = a._buf[i] + b._buf[i];
    }
    return res;
  }
  friend Vec operator+(Vec &&a, const Vec &b) {
    std::cout << "friend Vec operator+ (const Vec&& a, const Vec& b)"
              << std::endl;
    if (a._n != b._n) {
      std::cout << "Dimension not match!" << std::endl;
      exit(1);
    }
    Vec res(std::move(a));
    for (int i = 0; i < res._n; i++) {
      res._buf[i] = res._buf[i] + b._buf[i];
    }
    return res;
  }
  ~Vec() {
    std::cout << "~Vec()" << std::endl;
    if (_buf != nullptr) {
      std::cout << "Releasing" << std::endl;
      delete[] _buf;
      _buf = nullptr;
    }
  }
};

int main() {
  Vec v1(3), v2(3), v3(3), v4(3);
  // v1 + v2 create an anonymous object, which is a r-value.
  Vec v5 = v1 + v2 + v3 + v4;
  return 0;
}