//
// Created by 丁麓然 on 9/22/23.
//

#include "../../inc/datastructure/customlist.h"
#include <exception>
#include <istream>
#include <stdexcept>
#include <system_error>

namespace custom {
template <typename T>
list<T>::list() : _head(nullptr), _tail(nullptr), _size(0) {}
template <typename T> list<T>::list(T *arr, int length) {
  _head = nullptr;
  _tail = nullptr;
  for (int i = 0; i < length; i++) {
    push_back(arr[i]);
  }
}
template <typename T> list<T>::list(const list<T> &l) {
  _head = nullptr;
  _tail = nullptr;
  _Node *p = l._head;
  while (p != nullptr) {
    push_back(p->data);
    p = p->next;
  }
}
template <typename T> list<T>::~list() { clear(); }
template <typename T> list<T> &list<T>::operator=(const list<T> &l) {
  if (this == &l) {
    return *this;
  }
  clear();
  _Node *p = l._head;
  while (p != nullptr) {
    push_back(p->data);
    p = p->next;
  }
  return *this;
}
template <typename T> T &list<T>::operator[](int index) {
  if (index < 0 or index >= size()) {
    throw std::out_of_range("Index out of range");
  }
  _Node *p = _head;
  for (int i = 0; i < index; i++) {
    p = p->next;
  }
  return p->data;
}
template <typename T> T list<T>::operator[](int index) const {
  if (index < 0 or index >= size()) {
    throw std::out_of_range("Index out of range");
  }
  _Node *p = _head;
  for (int i = 0; i < index; i++) {
    p = p->next;
  }
  return p->data;
}
template <typename T> list<T> list<T>::operator+(const list<T> &l) const {
  list<T> new_list(*this);
  new_list += l;
  return new_list;
}
template <typename T> void list<T>::operator+=(const list<T> &l) {
  _Node *p = l._head;
  while (p != nullptr) {
    push_back(p->data);
    p = p->next;
  }
}
template <typename T> bool list<T>::operator==(const list<T> &l) const {
  if (size() != l.size()) {
    return false;
  }
  _Node *p = _head;
  _Node *q = l._head;
  while (p != nullptr) {
    if (p->data != q->data) {
      return false;
    }
    p = p->next;
    q = q->next;
  }
  return true;
}
template <typename T> bool list<T>::operator!=(const list<T> &l) const {
  return not(*this == l);
}
template <typename T>
std::wostream &list<T>::operator<<(std::wostream &os) const {
  _Node *p = _head;
  while (p != nullptr) {
    os << p->data << " ";
    p = p->next;
  }
  return os;
}
std::wistream &operator>>(std::wistream &is, list<wchar_t> &l) {
  l.clear();
  wchar_t c;
  while (is.get(c)) {
    l.push_back(c);
  }
  return is;
}
template <typename T> int list<T>::size() const { return _size; }
template <typename T> bool list<T>::empty() const { return _size == 0; }
template <typename T> void list<T>::clear() {
  while (not empty()) {
    pop_front();
  }
  _tail = nullptr;
  _size = 0;
}
template <typename T> T list<T>::front() const {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return _head->data;
}
template <typename T> T list<T>::back() const {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  return _tail->data;
}
template <typename T> void list<T>::push_back(const T &data) {
  _Node *new_node = nullptr;
  try {
    new_node = new _Node(data);
  } catch (std::exception &e) {
    throw std::system_error(std::error_code(1, std::generic_category()),
                            "Memory allocation failed");
  }
  if (_head == nullptr) {
    _head = new_node;
    _tail = new_node;
  } else {
    _tail->next = new_node;
    _tail = new_node;
  }
  _size++;
}
template <typename T> void list<T>::push_front(const T &data) {
  _Node *new_node = nullptr;
  try {
    new_node = new _Node(data);
  } catch (std::exception &e) {
    throw std::system_error(std::error_code(1, std::generic_category()),
                            "Memory allocation failed");
  }
  if (_head == nullptr) {
    _head = new_node;
    _tail = new_node;
  } else {
    new_node->next = _head;
    _head = new_node;
  }
  _size++;
}
template <typename T> void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
  } else {
    _Node *p = _head;
    while (p->next != _tail) {
      p = p->next;
    }
    delete _tail;
    _tail = p;
    _tail->next = nullptr;
  }
  _size--;
}
template <typename T> void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
  } else {
    _Node *p = _head;
    _head = _head->next;
    delete p;
  }
  _size--;
}
template <typename T> void list<T>::insert(int index, const T &data) {
  if (index < 0 or index > size()) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    push_front(data);
  } else if (index == size()) {
    push_back(data);
  } else {
    _Node *new_node = nullptr;
    try {
      new_node = new _Node(data);
    } catch (std::exception &e) {
      throw std::system_error(std::error_code(1, std::generic_category()),
                              "Memory allocation failed");
    }
    _Node *p = _head;
    for (int i = 0; i < index - 1; i++) {
      p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
    _size++;
  }
}
template <typename T> void list<T>::insert(int index, list<T>) {}
template <typename T> void list<T>::remove(int index) {
  if (index < 0 or index >= size()) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    pop_front();
  } else if (index == size() - 1) {
    pop_back();
  } else {
    _Node *p = _head;
    for (int i = 0; i < index - 1; i++) {
      p = p->next;
    }
    _Node *q = p->next;
    p->next = q->next;
    delete q;
    _size--;
  }
}
template <typename T> void list<T>::remove(const T &data) {
  int idx = search(data);
  if (idx == -1) {
    throw std::out_of_range("Data not found");
  }
  remove(search(data));
}
template <typename T> void list<T>::remove(int index, int length) {
  if (index < 0 or index >= size()) {
    throw std::out_of_range("Index out of range");
  }
  if (index + length > size()) {
    throw std::out_of_range("Index out of range");
  }
  for (int i = 0; i < length; i++) {
    remove(index);
  }
}
template <typename T> int list<T>::search(const T &data) const {
  _Node *p = _head;
  int index = 0;
  while (p != nullptr) {
    if (p->data == data) {
      return index;
    }
    p = p->next;
    index++;
  }
  return -1;
}
template <typename T> void list<T>::replace(int index, const T &data) {
  *this[index] = data;
}
template <typename T>
void list<T>::replace(int index, int length, const T &data) {
  if (index < 0 or index >= size()) {
    throw std::out_of_range("Index out of range");
  }
  for (int i = 0; i < _size and i < length; i++) {
    replace(index, data);
  }
}
template <typename T> void list<T>::reverse() {
  if (empty()) {
    return;
  }
  _Node *p = _head;
  _Node *q = _head->next;
  _Node *r = nullptr;
  while (q != nullptr) {
    p->next = r;
    r = p;
    p = q;
    q = q->next;
  }
  p->next = r;
  _tail = _head;
  _head = p;
}
template <typename T> int list<T>::count(const T &data) const {
  int cnt = 0;
  _Node *p = _head;
  while (p != nullptr) {
    if (p->data == data) {
      cnt++;
    }
    p = p->next;
  }
  return cnt;
}
} // namespace custom