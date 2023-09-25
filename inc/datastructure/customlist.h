//
// Created by 丁麓然 on 9/22/23.
//

#ifndef STRING_OPERATION_SENTENCELIST_H
#define STRING_OPERATION_SENTENCELIST_H

#include <iostream>

namespace custom {
template <typename T> class list {
private:
  struct _Node {
    T data;
    _Node *next;

    _Node() : next(nullptr) {}
    _Node(const T data) : data(data), next(nullptr) {}
    _Node(const T data, _Node *next) : data(data), next(next) {}
  };
  _Node *_head;
  _Node *_tail;
  int _size;

public:
  list();
  list(T *, int);
  list(const list<T> &);
  ~list();
  list<T> &operator=(const list<T> &);
  T &operator[](int);
  T operator[](int) const;
  list<T> operator+(const list<T> &) const;
  void operator+=(const list<T> &);
  bool operator==(const list<T> &) const;
  bool operator!=(const list<T> &) const;
  std::wostream &operator<<(std::wostream &) const;
  std::wistream &operator>>(std::wistream &);
  int size() const;
  bool empty() const;
  void clear();
  T front() const;
  T back() const;
  void push_back(const T &);
  void push_front(const T &);
  void pop_back();
  void pop_front();
  void insert(int, const T &);
  void insert(int, list<T>);
  void remove(int);
  void remove(const T &);
  void remove(int, int);
  int search(const T &) const;
  void replace(int, const T &);
  void replace(int, int, const T &);
  void reverse();
  int count(const T &) const;
};
} // namespace custom

#endif // STRING_OPERATION_SENTENCELIST_H
