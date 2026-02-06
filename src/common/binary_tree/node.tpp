#include "binary_tree.h"

namespace s21 {

// operators for *node_* structure
// *--------------------------------------------------------------------------*
// *--------------------------------------------------------------------------*

// compares keys
template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::node_::operator<(const node_ &other) const {
  if constexpr (!std::is_void_v<T_>) {
    return data_.first < other.data_.first;
  } else {
    return data_ < other.data_;
  }
}

// compares keys
template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::node_::operator>(const node_ &other) const {
  if constexpr (!std::is_void_v<T_>) {
    return data_.first > other.data_.first;
  } else {
    return data_ < other.data_;
  }
}

// compares keys
template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::node_::operator!=(const node_ &other) const {
  if constexpr (!std::is_void_v<T_>) {
    return data_.first != other.data_.first;
  } else {
    return data_ < other.data_;
  }
}

// compares keys
template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::node_::operator==(const node_ &other) const {
  if constexpr (!std::is_void_v<T_>) {
    return data_.first == other.data_.first;
  } else {
    return data_ == other.data_;
  }
}

}  // namespace s21