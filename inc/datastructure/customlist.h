//
// Created by 丁麓然 on 9/22/23.
//

#ifndef STRING_OPERATION_CUSTOMLIST_H
#define STRING_OPERATION_CUSTOMLIST_H

#include <initializer_list>
#include <iostream>

namespace custom {
template <typename T> class list {
private:
  struct _Node {
    T data;
    _Node *next;

    _Node() : next(nullptr) {}
    _Node(const T d) : next(nullptr) { data = d; }
    _Node(const T d, _Node *next) : next(next) { data = d; }
  };
  _Node *_head;
  _Node *_tail;
  int _size;

public:
  list() : _head(nullptr), _tail(nullptr), _size(0) {}
  list(T *arr, int length) {
    _head = nullptr;
    _tail = nullptr;
    for (int i = 0; i < length; i++) {
      push_back(arr[i]);
    }
  }
  list(const list<T> &l) {
    _head = nullptr;
    _tail = nullptr;
    _Node *p = l._head;
    while (p != nullptr) {
      push_back(p->data);
      p = p->next;
    }
  }
  list(const std::initializer_list<T> &l) {
    _head = nullptr;
    _tail = nullptr;
    for (auto &i : l) {
      push_back(i);
    }
  }
  ~list() {
    while (not empty()) {
      pop_front();
    }
    _tail = nullptr;
    _size = 0;
  }
  list<T> &operator=(const list<T> &l) {
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
  T &operator[](int index) {
    if (index < 0 or index >= size()) {
      throw std::out_of_range("Index out of range");
    }
    _Node *p = _head;
    for (int i = 0; i < index; i++) {
      p = p->next;
    }
    return p->data;
  }
  T operator[](int index) const {
    if (index < 0 or index >= size()) {
      throw std::out_of_range("Index out of range");
    }
    _Node *p = _head;
    for (int i = 0; i < index; i++) {
      p = p->next;
    }
    return p->data;
  }
  friend list<T> operator+(const list<T> &l1, const list<T> &l2) {
    list<T> temp(l1);
    temp += l2;
    return temp;
  }
  void operator+=(const list<T> &l) {
    _Node *p = l._head;
    while (p != nullptr) {
      push_back(p->data);
      p = p->next;
    }
  }
  bool operator==(const list<T> &l) const {
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
  bool operator!=(const list<T> &l) const { return not(*this == l); }
  friend std::wostream &operator<<(std::wostream &os, const list<T> &l) {
    _Node *p = l._head;
    while (p != nullptr) {
      os << p->data << " ";
      p = p->next;
    }
    return os;
  }

  friend std::wistream &operator>>(std::wistream &is, list<T> &l) {
    wchar_t c;
    while (is.get(c)) {
      l.push_back(c);
    }
    return is;
  }

  int size() const { return _size; }
  bool empty() const { return _size == 0; }
  void clear() {
    while (not empty()) {
      pop_front();
    }
    _tail = nullptr;
    _size = 0;
  }
  T front() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return _head->data;
  }
  T back() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return _tail->data;
  }
  void push_back(const T &data) {
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
  void push_front(const T &data) {
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
  void pop_back() {
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
  void pop_front() {
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
  void insert(int index, const T &data) {
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
  void insert(int index, const list<T> &l) {
    if (index < 0 or index > size()) {
      throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
      *this = l + *this;
    } else if (index == size()) {
      *this = *this + l;
    } else {
      _Node *p = _head;
      for (int i = 0; i < index - 1; i++) {
        p = p->next;
      }
      _Node *q = p->next;
      p->next = l._head;
      l._tail->next = q;
      _size += l._size;
    }
  }
  void highlight_show(const list<int> &to_highlight,
                      const char mode = 0) const {
    _Node *p = _head;
    int index = 0;
    switch (mode) {
    case 0:
      while (p != nullptr) {
        if (to_highlight.exist(index)) {
          std::wcout << L"\033[7m" << p->data << L"\033[0m";
        } else {
          std::wcout << p->data;
        }
        std::wcout << L" ";
        p = p->next;
        index++;
      }
    case 1:
      while (p != nullptr) {
        if (to_highlight.exist(index)) {
          std::wcout << L"\033[7m" << L"\033[2m" << index << L"\033[0m"
                     << L"\033[7m" << p->data << L"\033[0m";
        } else {
          std::wcout << L"\033[2m" << index << L"\033[0m" << p->data;
        }
        std::wcout << L" ";
        p = p->next;
        index++;
      }
    }
  }
  void show(const char mode = 0) const {
    _Node *p = _head;
    switch (mode) {
    case 0:
      std::wcout << *this;
      break;
    case 1:
      int index = 0;
      while (p != nullptr) {
        std::wcout << L"\033[2m" << index << L"\033[0m" << p->data << L"\t";
        p = p->next;
        index++;
      }
    }
  }
  void remove(int index) {
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
  void remove(const T &data) {
    bool idx = exist(data);
    if (not idx) {
      throw std::out_of_range("Data not found");
    }
    for (int i = 0; i < _size; i++) {
      if ((*this)[i] == data) {
        remove(i);
        i--;
      }
    }
  }
  void remove(int index, int length) {
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
  bool exist(const T data) const {
    _Node *p = _head;
    int index = 0;
    while (p != nullptr) {
      if (p->data == data) {
        return true;
      }
      p = p->next;
      index++;
    }
    return false;
  }
  list<int> find(const T &data) const {
    _Node *p = _head;
    list<int> result;
    int index = 0;
    while (p != nullptr) {
      if (p->data == data) {
        result.push_back(index);
      }
      p = p->next;
      index++;
    }
    return result;
  }
  void replace(int index, const T &data) { this->operator[](index) = data; }
  void reverse() {
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
  int count(const T &data) const {
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
};

} // namespace custom

#endif // STRING_OPERATION_CUSTOMLIST_H
