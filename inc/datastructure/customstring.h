//
// Created by 丁麓然 on 9/22/23.
//

#ifndef STRING_OPERATION_CUSTOMSTRING_H
#define STRING_OPERATION_CUSTOMSTRING_H

#include "customlist.h"
#include <iostream>
#include <string>

#define DEFAULT_CAPACITY 16 * sizeof(wchar_t)

namespace custom {

class string {
private:
  wchar_t *_data;
  int _length;
  int _capacity;

public:
  string();
  string(const char *);
  string(const wchar_t *);
  string(const string &);
  string(const std::string &);
  ~string();
  string &operator=(const string &);
  string &operator+=(const string &);
  string operator+(const string &);
  wchar_t &operator[](int);
  wchar_t operator[](int) const;
  bool operator==(const string &) const;
  std::wostream &operator<<(std::wostream &) const;
  std::wistream &operator>>(std::wistream &);
  operator std::string() const;
  operator const wchar_t *() const;

  int size() const;
  int length() const;
  int capacity() const;
  bool empty() const;
  void clear();
  string reverse() const;
  list<string> split(const wchar_t *delimiters = nullptr) const;
};

double string_similarity(const string &, const string &);

} // namespace custom

#endif // STRING_OPERATION_CUSTOMSTRING_H
