#include <iostream>

struct myInt {
  int value;
  operator int() { return value; }
};

int main() {
  myInt obj;
  int myInt = static_cast<int>(obj);  // operator int() provided
  std::cout << myInt;
  return 0;
}