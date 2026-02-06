#include "binary_tree.h"

namespace s21 {

// public part of *BinaryTree* class:
//____----____----____----____----____----____----____----____----____----____
//----____----____----____----____----____----____----____----____----____----

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::BinaryTree() {
  nulling_data();
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::BinaryTree(
    std::initializer_list<value_type> const &items) {
  nulling_data();
  for (const auto &item : items) {
    insert(item);
  }
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::BinaryTree(const BinaryTree &other)
    : root_(nullptr), size_(other.size_) {
  if (size_) {
    root_ = copy_tree(other.root_, nullptr);
  }
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::BinaryTree(BinaryTree &&other)
    : root_(other.root_), size_(other.size_) {
  other.nulling_data();
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_>::~BinaryTree() {
  clear();
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_> &BinaryTree<Key_, T_>::operator=(const BinaryTree &other) {
  root_ = copy_tree(other.root_, nullptr);
  size_ = other.size_;
  return *this;
}

template <typename Key_, typename T_>
BinaryTree<Key_, T_> BinaryTree<Key_, T_>::operator=(BinaryTree &&other) {
  if (this != &other) {
    clear();
    root_ = other.root_;
    size_ = other.size_;
    other.nulling_data();
  }
  return *this;
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::clear() {
  clear_subtree(root_);
  nulling_data();
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::insert(const value_type &value) {
  node_ *find_one;
  if constexpr (std::is_void_v<T_>) {
    find_one = find_node_node_(value);
  } else {
    find_one = find_node_node_(value.first);
  }
  if (find_one == nullptr) {
    node_ *new_node =
        new node_{value, nullptr, nullptr, nullptr, node_::Color::RED};
    if (root_ == nullptr) {
      new_node->color_ = node_::Color::BLACK;
      root_ = new_node;
    } else {
      insert_node(new_node);
      balance_tree_fix_insert(new_node);
    }
    ++size_;
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::remove_node(iterator pos) {
  node_ *current = pos.current_;
  if (current != nullptr) {
    // балансировка производится внутри каждого метода удаления ниже
    if (has_node_both_children(current)) {
      remove_node_with_two_child(current);
    } else if (has_only_one_child(current)) {
      remove_node_with_one_child(current);
    } else {
      remove_node_with_no_children(current);
    }
    --size_;
  } else {
    throw std::out_of_range("remove_node(): trying to delete nullptr node");
  }
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator
BinaryTree<Key_, T_>::find_node_iterator(const key_type &needed) {
  node_ *current = root_;
  while (current != nullptr) {
    if constexpr (!std::is_void_v<T_>) {  // T_ не void (map)
      if (needed < current->data_.first) {
        current = current->left_;
      } else if (needed > current->data_.first) {
        current = current->right_;
      } else {
        // нашли
        return iterator(current, *this);
      }
    } else {  // T_ void (set)
      if (needed < current->data_) {
        current = current->left_;
      } else if (needed > current->data_) {
        current = current->right_;
      } else {
        // нашли
        return iterator(current, *this);
      }
    }
  }

  return iterator(nullptr, *this);
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *BinaryTree<Key_, T_>::find_node_node_(
    const key_type &needed) {
  node_ *current = root_;
  while (current != nullptr) {
    if constexpr (!std::is_void_v<T_>) {
      if (needed < current->data_.first) {
        current = current->left_;
      } else if (needed > current->data_.first) {
        current = current->right_;
      } else {
        // нашли
        return current;
      }
    } else {
      if (needed < current->data_) {
        current = current->left_;
      } else if (needed > current->data_) {
        current = current->right_;
      } else {
        // нашли
        return current;
      }
    }
  }
  return nullptr;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *BinaryTree<Key_, T_>::get_node(
    iterator it) {
  if (it.current_) {
    return it.current_;
  } else {
    throw std::out_of_range("get_node(): current node is nullptr!");
  }
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator BinaryTree<Key_, T_>::begin() {
  node_ *start = find_min_node_from_current(root_);
  if (start == nullptr) throw std::out_of_range("begin(): Tree is empty");
  return iterator(start, *this);
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::iterator BinaryTree<Key_, T_>::end() {
  // if (empty()) throw std::out_of_range("end(): tree is empty");
  return iterator(nullptr, *this);
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::empty() const {
  return size_ == 0;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::size_type BinaryTree<Key_, T_>::size() const {
  return size_;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::size_type BinaryTree<Key_, T_>::max_size()
    const {
  return std::numeric_limits<size_type>::max() / sizeof(node_);
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::contains(const key_type &key) {
  node_ *found_one = find_node_node_(key);
  return found_one != nullptr;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_balanced() {
  return is_root_black() && is_black_count_ok() && check_red_red(root_);
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *BinaryTree<Key_, T_>::find_max_node()
    const {
  if (!empty()) {
    return find_max_node_from_current(root_);
  } else
    return nullptr;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *BinaryTree<Key_, T_>::find_min_node()
    const {
  if (!empty()) {
    return find_min_node_from_current(root_);
  } else {
    return nullptr;
  }
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_there_such_node(const key_type &key) {
  node_ *result = find_node_node_(key);
  return !(result == nullptr);
}

}  // namespace s21