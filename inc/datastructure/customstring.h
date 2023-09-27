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
  string(const char *const);
  string(const wchar_t *const);
  string(const string &);
  string(const std::string &);
  string(const wchar_t *const, int);
  ~string();
  string &operator=(const string &);
  string &operator+=(const string &);
  string operator+(const string &);
  wchar_t &operator[](int);
  wchar_t operator[](int) const;
  bool operator==(const string &) const;
  friend std::wostream &operator<<(std::wostream &, const string &);
  friend std::wistream &operator>>(std::wistream &, const string &);
  operator std::string() const;
  operator const wchar_t *() const;

  int size() const;
  int length() const;
  int capacity() const;
  bool empty() const;
  void clear();
  int find(const wchar_t *const) const;
  int find_first_of(const wchar_t *const, int = 0) const;
  string substr(int) const;
  string substr(int, int) const;
  string reverse() const;
  list<string> split(const wchar_t delimiters = L' ') const;
};

double string_similarity(const string &, const string &);

} // namespace custom

#endif // STRING_OPERATION_CUSTOMSTRING_H
