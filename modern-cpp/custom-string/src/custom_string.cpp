#include "custom_string.h"

#include <string.h>

#include <utility>

mystring::mystring() : size_{0}, buf_{new char[1]{'\0'}} {}

mystring::mystring(const char* str)
    : size_{strlen(str)}, buf_{new char[size_ + 1]} {
  for (size_t i = 0; i < size_; i++) {
    buf_[i] = str[i];
  }
  buf_[size_] = '\0';
}

mystring::mystring(const mystring& mystr)
    : size_{mystr.size_}, buf_{new char[size_ + 1]} {
  for (size_t i = 0; i < size_; i++) {
    buf_[i] = mystr.buf_[i];
  }
  buf_[size_] = '\0';
}

mystring::mystring(mystring&& mystr) { *this = std::move(mystr); }

char& mystring::operator[](size_t i) {
  if (i >= size_) {
    throw std::out_of_range("index " + std::to_string(i) + "out of range " +
                            std::to_string(size_));
  }
  return *(buf_ + i);
};

const char& mystring::operator[](size_t i) const {
  if (i >= size_) {
    throw std::out_of_range("index " + std::to_string(i) + "out of range " +
                            std::to_string(size_));
  }
  return *(buf_ + i);
}

mystring& mystring::operator=(const mystring& mystr) {
  if (this != &mystr) {
    if (size_ != mystr.size_) {
      delete[] buf_;
      size_ = mystr.size_;
      buf_ = new char[size_ + 1];
    }
    for (size_t i = 0; i <= size_; i++) {
      buf_[i] = mystr.buf_[i];
    }
  }
  return *this;
}

int main() { return 0; }