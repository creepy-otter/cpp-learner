#include "custom_string.h"

#include <string.h>

#include <algorithm>
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

mystring::~mystring() {
  if (buf_ != nullptr) {
    delete[] buf_;
  }
}

char& mystring::operator[](size_t i) {
  if (i >= size_) {
    throw std::out_of_range("index " + std::to_string(i) + " out of range " +
                            std::to_string(size_));
  }
  return *(buf_ + i);
};

const char& mystring::operator[](size_t i) const {
  if (i >= size_) {
    throw std::out_of_range("index " + std::to_string(i) + " out of range " +
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

mystring& mystring::operator+=(const mystring& mystr) {
  if (mystr.size_ != 0) {
    char* new_buf = new char[size_ + mystr.size_ + 1];
    auto p = std::copy_n(buf_, size_, new_buf);
    std::copy_n(mystr.buf_, mystr.size_ + 1, p);
    delete[] buf_;
    buf_ = new_buf;
    size_ = size_ + mystr.size_;
  }
  return *this;
}

size_t mystring::length() const { return size_; }

mystring operator+(const mystring& mystr1, const mystring& mystr2) {
  mystring res;
  res.size_ = mystr1.size_ + mystr2.size_;
  res.buf_ = new char[res.size_ + 1];
  auto p = std::copy_n(mystr1.buf_, mystr1.size_, res.buf_);
  std::copy_n(mystr2.buf_, mystr2.size_ + 1, p);
  return res;
}

std::ostream& operator<<(std::ostream& os, const mystring& mystr) {
  for (size_t i = 0; i < mystr.size_; i++) {
    os << mystr[i];
  }
  return os;
}

int main() {
  const char* p = "This is a string.";
  mystring str1(p);
  const char* q = " This is another string.";
  mystring str2(q);
  mystring str3 = str1 + str2;  // RVO triggered.
  str1 += str2;
  return 0;
}