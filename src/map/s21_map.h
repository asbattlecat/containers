#ifndef S21_MAP_H
#define S21_MAP_H

#include <vector>

#include "../common/binary_tree/binary_tree.h"

namespace s21 {

template <typename Key_, typename T_>
class map : public BinaryTree<Key_, T_> {
 public:
  using key_type = Key_;
  using mapped_type = T_;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using typename BinaryTree<Key_, T_>::iterator;
  using typename BinaryTree<Key_, T_>::const_iterator;
  using size_type = std::size_t;

 private:
  using typename BinaryTree<Key_, T_>::node_;
  using BinaryTree<Key_, T_>::root_;
  using BinaryTree<Key_, T_>::size_;

 public:
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &other);
  map(map &&other);
  map operator=(map &&other);
  ~map();

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  /*
  методы есть в базовом классе BinaryTree:
    4. begin()
    5. end()
    6. empty()
    7. size()
    8. max_size()
    9. clear()
  */

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  bool contains(const key_type &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#include "map.tpp"

#endif