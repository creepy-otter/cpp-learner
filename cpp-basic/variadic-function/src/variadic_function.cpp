#include <stdarg.h>

#include <iostream>

// https://en.cppreference.com/w/c/variadic
int add_nums(int num, ...) {
  // holds the information needed by va_start, va_arg, va_end, and va_copy
  va_list args;
  int sum = 0;
  // va_start(va_list, parmN);
  // parmN: the named parameter preceding the first variable parameter
  va_start(args, num);
  for (int i = 0; i < num; i++) {
    // accesses the next variadic function argument
    sum += va_arg(args, int);
  }
  va_end(args);
  return sum;
}

int main(void) {
  std::cout << add_nums(3, 3, 6, 9) << std::endl;
  return 0;
}