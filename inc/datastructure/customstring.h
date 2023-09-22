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
  string(const char *str);
  string(const wchar_t *str);
  string(const string &str);
  string(const std::string &str);
  ~string();
  string &operator=(const string &str);
  string &operator+=(const string &str);
  string operator+(const string &str);
  wchar_t &operator[](int index);
  wchar_t operator[](int index) const;
  bool operator==(const string &str) const;
  std::wostream &operator<<(std::wostream &os) const;
  std::wistream &operator>>(std::wistream &is);
  operator std::string() const;
  operator const wchar_t *() const;

  int size() const;
  int length() const;
  int capacity() const;
  bool empty() const;
  void clear();
  string reverse() const;
  list<string> split(const wchar_t *delimiters) const;
};

double string_similarity(const string &str1, const string &str2);

} // namespace custom

#endif // STRING_OPERATION_CUSTOMSTRING_H