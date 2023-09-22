//
// Created by 丁麓然 on 9/22/23.
//

#ifndef STRING_OPERATION_SENTENCELIST_H
#define STRING_OPERATION_SENTENCELIST_H

namespace custom {
template <typename T> class list {
private:
  struct _Node {
    T data;
    _Node *next;
  };
  _Node *_head;
  _Node *_tail;

public:
  list();
  list(T *arr, int length);
  list(const list<T> &l);
  ~list();
  list<T> &operator=(const list<T> &l);
  T &operator[](int index);
  T operator[](int index) const;
  int size() const;
  bool empty() const;
  void clear();
  void push_back(const T &data);
  void push_front(const T &data);
  void pop_back();
  void pop_front();
  void insert(int index, const T &data);
  void remove(int index);
  void remove(const T &data);
  void reverse();
};
} // namespace custom

#endif // STRING_OPERATION_SENTENCELIST_H
