#include "s21_map.h"

namespace s21 {

template <typename Key_, typename T_>
map<Key_, T_>::map() : BinaryTree<Key_, T_>() {}

template <typename Key_, typename T_>
map<Key_, T_>::map(std::initializer_list<value_type> const &items)
    : BinaryTree<Key_, T_>(items) {}

template <typename Key_, typename T_>
map<Key_, T_>::map(const map &other) : BinaryTree<Key_, T_>(other) {}

template <typename Key_, typename T_>
map<Key_, T_>::map(map &&other) : BinaryTree<Key_, T_>(std::move(other)) {}

template <typename Key_, typename T_>
map<Key_, T_> map<Key_, T_>::operator=(map &&other) {
  BinaryTree<Key_, T_>::operator=(std::move(other));
  return *this;
}

template <typename Key_, typename T_>
map<Key_, T_>::~map() {
  BinaryTree<Key_, T_>::clear();
}

template <typename Key_, typename T_>
typename map<Key_, T_>::mapped_type &map<Key_, T_>::at(const key_type &key) {
  if (size_ == 0) throw std::out_of_range("at(): Container is empty");
  node_ *node = BinaryTree<Key_, T_>::find_node_node_(key);
  if (node) {
    return node->data_.second;
  } else {
    throw std::out_of_range("at(): there is no such key");
  }
}

template <typename Key_, typename T_>
typename map<Key_, T_>::mapped_type &map<Key_, T_>::operator[](
    const key_type &key) {
  if (size_ == 0) throw std::out_of_range("operator[]: Container is empty");
  node_ *node = BinaryTree<Key_, T_>::find_node_node_(key);
  if (node == nullptr) {
    // не нашли
    throw std::out_of_range("operator[]: there is no such key");
  }
  return node->data_.second;
}

template <typename Key_, typename T_>
std::pair<typename map<Key_, T_>::iterator, bool> map<Key_, T_>::insert(
    const value_type &value) {
  if (!contains(value.first)) {
    BinaryTree<Key_, T_>::insert(value);
    iterator it = BinaryTree<Key_, T_>::find_node_iterator(value.first);
    return {it, true};
  } else {
    return {iterator(nullptr, *this), false};
  }
}

template <typename Key_, typename T_>
std::pair<typename map<Key_, T_>::iterator, bool> map<Key_, T_>::insert(
    const key_type &key, const mapped_type &obj) {
  value_type value = {key, obj};
  if (!contains(key)) {
    BinaryTree<Key_, T_>::insert(value);
    iterator it = BinaryTree<Key_, T_>::find_node_iterator(key);
    return {it, true};
  } else {
    return {iterator(nullptr, *this), false};
  }
}

template <typename Key_, typename T_>
std::pair<typename map<Key_, T_>::iterator, bool>
map<Key_, T_>::insert_or_assign(const key_type &key, const mapped_type &obj) {
  value_type value = {key, obj};
  if (!contains(key)) {
    BinaryTree<Key_, T_>::insert(value);
    iterator it = BinaryTree<Key_, T_>::find_node_iterator(key);
    return {it, true};
  } else {
    node_ *node = BinaryTree<Key_, T_>::find_node_node_(key);
    node->data_.second = obj;
    iterator it = BinaryTree<Key_, T_>::find_node_iterator(key);
    return {it, true};
  }
}

template <typename Key_, typename T_>
void map<Key_, T_>::erase(iterator pos) {
  BinaryTree<Key_, T_>::remove_node(pos);
}

template <typename Key_, typename T_>
void map<Key_, T_>::swap(map &other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  } else
    throw std::invalid_argument("swap(): swaping the same objects");
}

template <typename Key_, typename T_>
void map<Key_, T_>::merge(map &other) {
  if (other.size()) {
    for (auto other_it = other.begin(); other_it != other.end();) {
      auto temp = other_it++;
      if (!contains(temp->first)) {
        insert(*temp);
        other.erase(temp);
      }
    }
  }
}

template <typename Key_, typename T_>
bool map<Key_, T_>::contains(const key_type &key) {
  return BinaryTree<Key_, T_>::is_there_such_node(key);
}

template <typename Key_, typename T_>
template <typename... Args>
std::vector<std::pair<typename map<Key_, T_>::iterator, bool>>
map<Key_, T_>::insert_many(Args &&...args) {
  size_type new_el_cnt = sizeof...(args);
  value_type temp[] = {std::forward<Args>(args)...};
  std::vector<std::pair<iterator, bool>> res;
  for (size_type i = 0; i < new_el_cnt; i++) {
    res.push_back(insert(temp[i]));
  }
  return res;
}

}  // namespace s21