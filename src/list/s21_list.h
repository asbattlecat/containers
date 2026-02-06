#ifndef S21_LIST_H
#define S21_LIST_H

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

#define EPSILON 9E-8

namespace s21 {
template <typename T_>
class list {
 public:
  typedef T_ value_type;
  typedef T_ &reference;
  typedef const T_ &const_reference;
  typedef std::size_t size_type;

  class ListConstIterator;
  class ListIterator;

  typedef ListIterator iterator;
  typedef ListConstIterator const_iterator;

 private:
  struct node_ {
    T_ data_;
    node_ *next_;
    node_ *prev_;
  };
  node_ *head_;
  node_ *tail_;
  size_type size_;

 public:
  // класс для итератора
  class ListIterator {
   private:
    node_ *ptr_;  // Указатель на текущий узел
    const list<T_> *parent_list_;
    friend class list<T_>;
    friend class ListConstIterator;

   public:
    ListIterator(node_ *ptr, const list<T_> *parent_list);
    ListIterator(const ListIterator &other);
    ListIterator &operator=(const ListIterator &other);
    reference operator*();
    ListIterator operator+(int n) const;
    ListIterator operator-(int n) const;
    ListIterator &operator++();
    ListIterator operator++(int);
    ListIterator &operator--();
    ListIterator operator--(int);
    bool operator==(const ListIterator &other) const;
    bool operator!=(const ListIterator &other) const;
  };

  // константный класс для итератора
  class ListConstIterator {
   private:
    const node_ *ptr_;
    const list<T_> *parent_list_;
    friend class list<T_>;
    friend class ListIterator;

   public:
    ListConstIterator(const node_ *ptr, const list<T_> *parent_list);
    ListConstIterator(const ListConstIterator &other);
    ListConstIterator(const ListIterator &other);
    ListConstIterator &operator=(const ListConstIterator &other);
    const_reference operator*() const;
    ListConstIterator operator+(int n) const;
    ListConstIterator operator-(int n) const;
    ListConstIterator &operator++();
    ListConstIterator operator++(int);
    ListConstIterator &operator--();
    ListConstIterator operator--(int);
    bool operator==(const ListConstIterator &other) const;
    bool operator!=(const ListConstIterator &other) const;
  };

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void sort();
  void unique();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  void create_list();
  void nulling_head_tail();
  void bubble_sort();
  bool is_sorted();
  void move_node(iterator pos, iterator &other_it, list &other);
  void unlink_node(iterator &pos);
  iterator find_iterator(const_iterator pos);
  size_type node_number(iterator pos);
};
}  // namespace s21

#include "list.tpp"
#include "list_const_iterator.tpp"
#include "list_iterator.tpp"

#endif