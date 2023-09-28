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
  /**
   * Finds the index of the first occurrence of any character from the given
   * string.
   *
   * This member function searches for the first occurrence of any character
   * from the given string (str) within the current string. It starts searching
   * from the specified start index (start). If the given string is null, it
   * returns -1. If the start index is out of range (less than 0 or greater than
   * or equal to the length of the string), it throws an `std::out_of_range`
   * exception. It iterates through the characters of the string, comparing each
   * character with the characters in the given string. If a match is found, it
   * returns the index of the matching character in the current string. If no
   * match is found, it returns -1.
   *
   * @param str The string containing characters to search for.
   * @param start The index to start searching from.
   * @return The index of the first occurrence of a matching character, or -1 if
   * no match is found.
   * @throws std::out_of_range if the start index is out of range.
   *
   * Example:
   * string myString = "Hello, World!";
   * int index = myString.find_first_of(L"lo");
   * // index is 3
   */
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
  /**
   * Extracts a substring from the current string.
   *
   * This member function extracts a substring from the current string, starting
   * at the specified start index (start) and with the specified length. If the
   * start index is out of range (less than 0 or greater than or equal to the
   * length of the string), it throws an `std::out_of_range` exception. If the
   * length is less than or equal to 0, it throws an `std::out_of_range`
   * exception. If the specified length is greater than the available characters
   * from the start index to the end of the string, the length is adjusted to
   * the maximum possible length. It returns a new string object that represents
   * the extracted substring.
   *
   * @param start The starting index of the substring.
   * @param length The length of the substring.
   * @return A new string object representing the extracted substring.
   * @throws std::out_of_range if the start index or length is out of range.
   *
   * Example:
   * string myString = "Hello, World!";
   * string subString = myString.substr(7, 5);
   * // subString is "World"
   */
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
  /**
   * Splits the current string into a list of substrings based on a delimiter
   * character.
   *
   * This member function splits the current string into a list of substrings
   * based on the specified delimiter character. If the length of the string is
   * 0, an empty list is returned. It iterates through the characters of the
   * string, searching for the delimiter character. Each substring between
   * delimiters is added to the result list using the substr function. The
   * substrings are added in the order they appear in the original string. The
   * resulting list of substrings is returned.
   *
   * @param delimiter The delimiter character to split the string.
   * @return A list of substrings obtained by splitting the string.
   *
   * Example:
   * string myString = "Hello, World!";
   * list<string> result = myString.split(',');
   * // result contains {"Hello", " World!"}
   */
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
    while (end < _length and _data[end] == delimiter) {
        ++end;
    }
    start = end;
  }
  return result;
}

} // namespace custom