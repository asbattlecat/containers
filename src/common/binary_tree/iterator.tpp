#include "binary_tree.h"

namespace s21 {

// public part of *iterator* class:
// *--------------------------------------------------------------------------*
// *--------------------------------------------------------------------------*

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::iterator::iterator(node_ *node, BinaryTree &tree)
    : current_(node), tree_(tree) {}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator &
BinaryTree<Key_, T_>::iterator::operator=(const iterator &other) {
  if (this != &other) {
    current_ = other.current_;
    tree_ = other.tree_;
  }
  return *this;
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::iterator::iterator(const iterator &other)
    : current_(other.current_), tree_(other.tree_) {}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::reference
BinaryTree<Key_, T_>::iterator::operator*() {
  if (current_ == nullptr)
    throw std::out_of_range("operator*(): current iterator node is nullptr");
  return current_->data_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_reference
BinaryTree<Key_, T_>::iterator::operator*() const {
  if (current_ == nullptr)
    throw std::out_of_range("operator*(): current iterator node is nullptr");
  return current_->data_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::pointer
BinaryTree<Key_, T_>::iterator::operator->() {
  if (current_ == nullptr)
    throw std::out_of_range("operator->(): current iterator node is nullptr");
  return &current_->data_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_pointer
BinaryTree<Key_, T_>::iterator::operator->() const {
  if (current_ == nullptr)
    throw std::out_of_range("operator->(): current iterator node is nullptr");
  return &current_->data_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator &
BinaryTree<Key_, T_>::iterator::operator++() {
  if (current_ == nullptr) {  // находимся на end()
    throw std::out_of_range(
        "operator++(): cannot increase iterator, it is end()");
  } else if (current_ == tree_.find_max_node()) {  // самый большой key
    current_ = nullptr;                            // переход на end()
  } else {
    move_to_bigger_key_iterator();
  }
  return *this;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator
BinaryTree<Key_, T_>::iterator::operator++(int) {
  iterator temp = *this;
  if (current_ == nullptr) {  // находимся на end()
    throw std::out_of_range(
        "operator++(int): cannot increase iterator, it is end()");
  } else if (current_ == tree_.find_max_node()) {  // самый большой key
    current_ = nullptr;                            // переход на end()
  } else {
    move_to_bigger_key_iterator();
  }
  return temp;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator &
BinaryTree<Key_, T_>::iterator::operator--() {
  if (current_ == nullptr) {  // находимся на end(), значит переходим на max_key
    if (!tree_.empty()) current_ = tree_.find_max_node();
  } else {
    if (current_ == tree_.find_min_node()) {  // находимся на begin()
      throw std::out_of_range(
          "operator--(): cannot decrease iterator, it is begin()");
    } else {
      move_to_smaller_key_iterator();
    }
  }
  return *this;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator
BinaryTree<Key_, T_>::iterator::operator--(int) {
  iterator temp = *this;
  if (current_ == nullptr) {  // находимся на end(), значит переходим на max_key
    if (!tree_.empty()) current_ = tree_.find_max_node();
  } else {
    if (current_ == tree_.find_min_node()) {  // находимся на begin()
      throw std::out_of_range(
          "operator--(int): cannot decrease iterator, it is begin()");
    } else {
      move_to_smaller_key_iterator();
    }
  }
  return temp;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::iterator::operator==(const iterator &other) const {
  return current_ == other.current_;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::iterator::operator!=(const iterator &other) const {
  return current_ != other.current_;
}

// private part of *iterator* class:
// *--------------------------------------------------------------------------*
// *--------------------------------------------------------------------------*

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::iterator::move_to_bigger_key_iterator() {
  if (current_ == nullptr) {
    return;
  }

  if (current_->right_ != nullptr) {
    current_ = current_->right_;
    while (current_->left_ != nullptr) {
      current_ = current_->left_;
    }
  } else {
    node_ *parent = current_->parent_;
    while (parent && current_ == parent->right_) {
      current_ = parent;
      parent = parent->parent_;
    }
    current_ = parent;
    if (current_ == nullptr) {
      return;
    }
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::iterator::move_to_smaller_key_iterator() {
  if (current_ != nullptr) {
    if (current_->left_ != nullptr) {
      current_ = current_->left_;

      while (current_->right_ != nullptr) current_ = current_->right_;
    } else {
      node_ *parent = current_->parent_;
      while (parent && current_ == parent->left_) {
        current_ = parent;
        parent = parent->parent_;
      }
      current_ = parent;
      if (current_ == nullptr) return;
    }
  } else
    return;
}

}  // namespace s21