#include "binary_tree.h"

namespace s21 {

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::const_iterator::const_iterator(const node_ *node,
                                                     const BinaryTree &tree)
    : current_(node), tree_(tree) {}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_iterator &
BinaryTree<Key_, T_>::const_iterator::operator=(const const_iterator &other) {
  if (this != &other) {
    current_ = other.current_;
    tree_ = other.tree_;
  }
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::const_iterator::const_iterator(
    const const_iterator &other)
    : current_(other.current_), tree_(other.tree_) {}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_reference
BinaryTree<Key_, T_>::const_iterator::operator*() {
  if (current_ == nullptr)
    throw std::out_of_range(
        "operator*(): current const_iterator node is nullptr");
  return current_->data_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_pointer
BinaryTree<Key_, T_>::const_iterator::operator->() {
  if (current_ == nullptr)
    throw std::out_of_range(
        "operator->(): current const_iterator node is nullptr");
  return &current_->data_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_iterator &
BinaryTree<Key_, T_>::const_iterator::operator++() {
  if (current_ == nullptr) {
    throw std::out_of_range(
        "operator++(): cannot increse const_iteraotr, it is end()");
  } else if (current_ == tree_.find_max_node()) {
    current_ = nullptr;
  } else {
    move_to_bigger_key_const_iter();
  }
  return *this;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_iterator
BinaryTree<Key_, T_>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  if (current_ == nullptr) {
    throw std::out_of_range(
        "operator++(): cannot increse const_iteraotr, it is end()");
  } else if (current_ == tree_.find_max_node()) {
    current_ = nullptr;
  } else {
    move_to_bigger_key_const_iter();
  }
  return temp;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_iterator &
BinaryTree<Key_, T_>::const_iterator::operator--() {
  if (current_ == nullptr) {
    if (!tree_.empty()) current_ = tree_.find_max_node();
  } else {
    if (current_ == tree_.find_min_node()) {
      throw std::out_of_range(
          "operator--(): cannot decrease const_iterator, it is begin()");
    } else {
      move_to_smaller_key_const_iter();
    }
  }
  return *this;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::const_iterator
BinaryTree<Key_, T_>::const_iterator::operator--(int) {
  const_iterator temp = *this;
  if (current_ == nullptr) {
    if (!tree_.empty()) current_ = tree_.find_max_node();
  } else {
    if (current_ == tree_.find_min_node()) {
      throw std::out_of_range(
          "operator--(): cannot decrease const_iterator, it is begin()");
    } else {
      move_to_smaller_key_const_iter();
    }
  }
  return temp;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::const_iterator::operator==(
    const const_iterator &other) const {
  return current_ == other.current_;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::const_iterator::operator!=(
    const const_iterator &other) const {
  return current_ != other.current_;
}

// ----------------------------------------------------------------------------
// private part of const_iterator:

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::const_iterator::move_to_bigger_key_const_iter() {
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
    if (current_ == nullptr) return;
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::const_iterator::move_to_smaller_key_const_iter() {
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