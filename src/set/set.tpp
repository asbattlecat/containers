#include "s21_set.h"

namespace s21 {

template <typename Key_>
set<Key_>::set() : BinaryTree<Key_, void>() {}

template <typename Key_>
set<Key_>::set(std::initializer_list<value_type> const &items)
    : BinaryTree<Key_, void>(items) {}

template <typename Key_>
set<Key_>::set(const set &other) : BinaryTree<Key_, void>(other) {}

template <typename Key_>
set<Key_>::set(set &&other) : BinaryTree<Key_, void>(std::move(other)) {
  // other.nulling_data();
}

template <typename Key_>
set<Key_> set<Key_>::operator=(set &&other) {
  BinaryTree<Key_, void>::operator=(std::move(other));
  other.nulling_data();
  return *this;
}

template <typename Key_>
set<Key_>::~set() {
  BinaryTree<Key_, void>::clear();
}

template <typename Key_>
std::pair<typename set<Key_>::iterator, bool> set<Key_>::insert(
    const value_type &key) {
  if (!contains(key)) {
    BinaryTree<Key_, void>::insert(key);
    iterator it = BinaryTree<Key_, void>::find_node_iterator(key);
    return {it, true};
  } else {
    return {iterator{nullptr, *this}, false};
  }
}

template <typename Key_>
void set<Key_>::erase(iterator pos) {
  BinaryTree<Key_, void>::remove_node(pos);
}

template <typename Key_>
void set<Key_>::swap(set &other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  } else
    throw std::invalid_argument("swap(): other is the same as this");
}

template <typename Key_>
void set<Key_>::merge(set &other) {
  if (!other.empty()) {
    for (auto other_it = other.begin(); other_it != other.end();) {
      auto temp = other_it++;
      if (!contains(*temp)) {
        insert(*temp);
        other.erase(temp);
      }
    }
  }
}

template <typename Key_>
bool set<Key_>::contains(const key_type &key) {
  return BinaryTree<Key_, void>::is_there_such_node(key);
}

template <typename Key_>
template <typename... Args>
std::vector<std::pair<typename set<Key_>::iterator, bool>>
set<Key_>::insert_many(Args &&...args) {
  size_type new_el_cnt = sizeof...(args);
  value_type temp[] = {std::forward<Args>(args)...};
  std::vector<std::pair<iterator, bool>> res;
  for (size_type i = 0; i < new_el_cnt; i++) {
    res.push_back(insert(temp[i]));
  }
  return res;
}

}  // namespace s21