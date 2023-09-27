//
// Created by 丁麓然 on 9/22/23.
//

#include "../../inc/datastructure/customstring.h"
#include "../../inc/datastructure/customlist.h"
#include <cwchar>
#include <iostream>
#include <istream>
#include <ostream>

namespace custom {
string::string() : _data(nullptr), _length(0), _capacity(DEFAULT_CAPACITY) {}
string::string(const char *const str) {
  if (str == nullptr) {
    _data = nullptr;
    _length = 0;
    _capacity = DEFAULT_CAPACITY;
  } else {
    size_t _length = strlen(str) + 1;
    _data = new wchar_t[_length];
    mbstowcs(_data, str, _length);
    _length = _length - 1;
    _capacity = _length;
  }
}
string::string(const wchar_t *const str) {
  if (str == nullptr) {
    _data = nullptr;
    _length = 0;
    _capacity = DEFAULT_CAPACITY;
  } else {
    _length = wcslen(str);
    _capacity = _length + 1;
    _data = new wchar_t[_capacity];
    wcscpy(_data, str);
  }
}
string::string(const string &str) {
  _length = str._length;
  _capacity = str._capacity;
  _data = new wchar_t[_capacity];
  wcscpy(_data, str._data);
}
string::string(const std::string &str) {
  size_t length = str.length();
  _length = length;
  _capacity = _length;
  try {
    _data = new wchar_t[_length + 1];
  } catch (std::bad_alloc &e) {
    std::cerr << "bad_alloc caught: " << e.what() << '\n';
    _data = nullptr;
    _length = 0;
    _capacity = 0;
    return;
  }
  if (_data) {
    mbstowcs(_data, str.c_str(), _length);
    _data[_length] = L'\0';
  } else {
    throw std::bad_alloc();
  }
}
string::string(const wchar_t *const str, int len) {
  _length = len;
  _capacity = len + 1;
  _data = new wchar_t[_capacity];
  wcsncpy(_data, str, len);
}
string::~string() { delete[] _data; }
string &string::operator=(const string &str) {
  if (this == &str) {
    return *this;
  }
  delete[] _data;
  _length = str._length;
  _capacity = str._capacity;
  _data = new wchar_t[_capacity];
  wcscpy(_data, str._data);
  return *this;
}
string &string::operator+=(const string &str) {
  if (str._length == 0) {
    return *this;
  }
  if (_length + str._length > _capacity) {
    wchar_t *temp = new wchar_t[_length + str._length];
    wcscpy(temp, _data);
    wcscat(temp, str._data);
    delete[] _data;
    _data = temp;
    _capacity = _length + str._length;
    _length = _length + str._length;
  } else {
    wcscat(_data, str._data);
    _length = _length + str._length;
  }
  return *this;
}
string string::operator+(const string &str) {
  string temp(*this);
  temp += str;
  return temp;
}
wchar_t &string::operator[](int index) { return _data[index]; }
wchar_t string::operator[](int index) const { return _data[index]; }
bool string::operator==(const string &str) const {
  if (_length != str._length) {
    return false;
  }
  for (int i = 0; i < _length; ++i) {
    if (_data[i] != str._data[i]) {
      return false;
    }
  }
  return true;
}
std::wostream &operator<<(std::wostream &os, const string &a) {
  os << a._data;
  return os;
}
std::wistream &operator>>(std::wistream &is, const string &a) {
  is >> a._data;
  return is;
}
string::operator std::string() const {
  std::string temp;
  temp.resize(_length);
  wcstombs(&temp[0], _data, _length);
  return temp;
}
string::operator const wchar_t *() const { return _data; }
int string::size() const { return _length; }
int string::length() const { return _length; }
int string::capacity() const { return _capacity; }
bool string::empty() const { return _length == 0; }
void string::clear() {
  delete[] _data;
  _data = nullptr;
  _length = 0;
  _capacity = DEFAULT_CAPACITY;
}
int string::find(const wchar_t *const str) const {
  if (str == nullptr) {
    return -1;
  }
  return find_first_of(str, 0);
}
int string::find_first_of(const wchar_t *const str, int start) const {
  if (str == nullptr) {
    return -1;
  }
  if (start < 0 || start >= _length) {
    throw std::out_of_range("start index out of range");
  }
  for (int i = start; i < _length; ++i) {
    for (int j = 0; str[j] != '\0'; ++j) {
      if (_data[i] == str[j]) {
        return i;
      }
    }
  }
  return -1;
}
string string::substr(int start) const {
  if (start < 0 || start >= _length) {
    return string();
  }
  return string(_data + start, _length - start);
}
string string::substr(int start, int length) const {
  if (start < 0 or start >= _length) {
    throw std::out_of_range("start index out of range");
  }
  if (length <= 0) {
    throw std::out_of_range("length out of range");
  } else if (length > _length - start) {
    length = _length - start;
  }
  return string(_data + start, length);
}
string string::reverse() const {
  string temp(*this);
  for (int i = 0; i < _length / 2; ++i) {
    wchar_t t = temp._data[i];
    temp._data[i] = temp._data[_length - i - 1];
    temp._data[_length - i - 1] = t;
  }
  return temp;
}
list<string> string::split(const wchar_t delimiter) const {
  list<string> result;
  if (_length == 0) {
    return result;
  }
  int start = 0;
  int end = 0;
  while (end < _length) {
    while (end < _length and _data[end] != delimiter) {
      ++end;
    }
    result.push_back(substr(start, end - start));
    start = end + 1;
    end = start;
  }
  return result;
}

double string_similarity(const string &str1, const string &str2) {
  if (str1.empty() || str2.empty()) {
    return 0;
  }
  int len1 = str1.length();
  int len2 = str2.length();
  int **dp = new int *[len1 + 1];
  for (int i = 0; i <= len1; ++i) {
    dp[i] = new int[len2 + 1];
  }
  for (int i = 0; i <= len1; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= len2; ++i) {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
      }
    }
  }
  double similarity = dp[len1][len2] * 1.0 / (len1 > len2 ? len1 : len2);
  for (int i = 0; i <= len1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return similarity;
}

} // namespace custom