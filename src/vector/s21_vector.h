#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

namespace s21 {
template <typename T_>
class vector {
 public:
  typedef T_ value_type;
  typedef T_& reference;
  typedef const T_& const_reference;
  typedef T_* iterator;
  typedef const T_* const_iterator;
  typedef std::size_t size_type;

 private:
  value_type* data_;
  size_type size_;
  size_type capacity_;

 public:
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);  // copy constructor
  vector(vector&& v);       // move constructor
  ~vector();
  vector& operator=(const vector& v);
  vector& operator=(vector&& v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  void delete_data();
  void create_data();
  void nulling_data();
  void move_data(vector&& other);
  void check_capacity();
  bool need_to_increase_capacity();
  void increase_capacity();
};
}  // namespace s21

#include "vector.tpp"

#endif