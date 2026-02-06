#ifndef S21_SET_H
#define S21_SET_H

#include <vector>

#include "../common/binary_tree/binary_tree.h"

namespace s21 {

template <typename Key_>
class set : public BinaryTree<Key_, void> {
  using typename BinaryTree<Key_, void>::node_;
  using BinaryTree<Key_, void>::root_;
  using BinaryTree<Key_, void>::size_;

 public:
  using key_type = Key_;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using typename BinaryTree<Key_, void>::iterator;
  using typename BinaryTree<Key_, void>::const_iterator;
  using size_type = std::size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&s);
  set operator=(set &&s);
  ~set();

  /*
          Следующие методы есть в базовом классе BinaryTree:
                  1. begin()
                  2. end()
                  3. empty()
                  4. size()
                  5. max_size()
                  6. clear()
  */

  std::pair<iterator, bool> insert(const value_type &value);

  bool contains(const key_type &key);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 public:
};

}  // namespace s21

#include "set.tpp"

#endif