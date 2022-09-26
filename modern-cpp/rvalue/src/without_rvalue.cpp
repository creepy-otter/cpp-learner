#include <iostream>
#include <string>
class Vec {
  int _n;
  int *_buf;
public:
  Vec(int n): _n(n) {
    std::cout << "Vec(int n)" << std::endl;
    _buf = new int[_n];
    for (int i = 0; i < _n; i++) {
      _buf[i] = 0;
    }
  }
  Vec(const Vec& v) {
    std::cout << "Vec(const Vec& v)" << std::endl;
    _n = v._n;
    _buf = new int[_n];
    for (int i = 0; i < _n; i++) {
      _buf[i] = 0;
    }
  }

  friend Vec operator+(const Vec& a, const Vec& b) {
    std::cout << "friend Vec operator+ (const Vec& a, const Vec& b)" << std::endl;
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
  Vec v5 = v1 + v2 + v3 + v4;
  return 0;
}