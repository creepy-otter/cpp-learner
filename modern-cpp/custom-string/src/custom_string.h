#pragma once

#include <iostream>
/***
 * Too naive implementation of string.
 * Constructor & Destructor
 * Operator overload
 */
class mystring {
 public:
  mystring();
  mystring(const char*);
  mystring(const mystring&);
  mystring(mystring&&);

  ~mystring();

  char& operator[](size_t);
  const char& operator[](size_t) const;

  mystring& operator=(const mystring&);
  mystring& operator+=(const mystring&);

  size_t length() const;

  // operator+ should be non-member function.
  friend mystring operator+(const mystring&, const mystring&);

  friend std::ostream& operator<<(std::ostream&, const mystring&);

 private:
  size_t size_;
  char* buf_;
};