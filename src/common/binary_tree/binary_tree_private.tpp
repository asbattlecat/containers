#include "binary_tree.h"

namespace s21 {

// private part of *BinaryTree* class:
//____----____----____----____----____----____----____----____----____----____
//----____----____----____----____----____----____----____----____----____----

//____----____----____----____----____----____----____----____----____----____
//----____----____----____----____----____----____----____----____----____----

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *BinaryTree<Key_, T_>::copy_tree(
    node_ *origin_node, node_ *parent) {
  if (origin_node == nullptr) return nullptr;  // узел пустой

  node_ *new_node = new node_{origin_node->data_, nullptr, nullptr, nullptr,
                              origin_node->color_};
  new_node->parent_ = parent;
  if (parent == nullptr) root_ = new_node;
  new_node->left_ = copy_tree(origin_node->left_, new_node);
  new_node->right_ = copy_tree(origin_node->right_, new_node);

  return new_node;
}

// ---                     вставка                                  ---
// ---                                                              ---

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::insert_node(node_ *new_node) {
  node_ *current = root_;
  node_ *parent = nullptr;
  // ищем место вставки
  while (current != nullptr) {
    parent = current;
    if (*new_node < *current) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  // теперь дошли до конца, и вставляем узел
  // у нашего узла появился папаша
  new_node->parent_ = parent;
  // а тут просто показывает какой new_node отросток у папаши
  if (parent) {
    if (*new_node < *parent) {
      parent->left_ = new_node;
    } else {
      parent->right_ = new_node;
    }
  }
}

// тут просто по правилам балансировки производится балансировка, тип по
// случаям, как по учебнику
template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::balance_tree_fix_insert(node_ *node) {
  while (node->parent_ && node->parent_->color_ == node_::Color::RED) {
    if (is_parent_left_child(node)) {
      node_ *uncle = nullptr;
      if (node->parent_ && node->parent_->parent_)
        uncle = node->parent_->parent_->right_;
      // если дядя красный
      if (uncle && uncle->color_ == node_::Color::RED) {
        node->parent_->color_ = node_::Color::BLACK;
        uncle->color_ = node_::Color::BLACK;
        node->parent_->parent_->color_ = node_::Color::RED;
        node = node->parent_->parent_;
      } else {
        // если дядя черный, или его нет
        // если текущий узел правый
        if (is_right_child(node)) {
          node = node->parent_;
          rotate_left(node);
        }
        // если дедушка красный, родитель черный
        node->parent_->color_ = node_::Color::BLACK;
        node->parent_->parent_->color_ = node_::Color::RED;
        rotate_right(node->parent_->parent_);
      }
    } else if (is_parent_right_child(node)) {
      node_ *uncle = node->parent_->parent_->left_;
      // если дядя красный
      if (uncle && uncle->color_ == node_::Color::RED) {
        node->parent_->color_ = node_::Color::BLACK;
        uncle->color_ = node_::Color::BLACK;
        node->parent_->parent_->color_ = node_::Color::RED;
        node = node->parent_->parent_;
      } else {
        // если дяди нет, текущий узел левый ребенок
        if (is_left_child(node)) {
          node = node->parent_;
          rotate_right(node);
        }
        // если дедушка красный, родитель черный
        node->parent_->color_ = node_::Color::BLACK;
        node->parent_->parent_->color_ = node_::Color::RED;
        rotate_left(node->parent_->parent_);
      }
    }
  }
  // чтоб наверняка черным был
  root_->color_ = node_::Color::BLACK;
}

// ---                      удаление                                 ---
// ---                                                               ---

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::remove_node_with_no_children(node_ *&node) {
  bool need_to_balance = is_node_black(node);
  node_ *parent = node->parent_;
  bool is_left = is_left_child(node);  // Запоминаем, был ли узел левым ребенком

  // Удаление узла
  if (parent) {
    if (is_left) {
      parent->left_ = nullptr;
    } else {
      parent->right_ = nullptr;
    }
  } else {  // у узла нет родителя, это корень дерева
    root_ = nullptr;
  }

  delete node;
  node = nullptr;

  if (parent && need_to_balance) {
    balance_tree_fix_remove(parent,
                            is_left);  // Передаем родителя и сторону удаления
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::remove_node_with_one_child(node_ *&node) {
  bool need_to_balance = (node->color_ == node_::Color::BLACK);
  node_ *parent = node->parent_;
  bool is_left = is_left_child(node);  // Запоминаем сторону удаления

  // Определяем ребенка
  node_ *child = (node->left_ != nullptr) ? node->left_ : node->right_;
  child->parent_ = parent;

  // Обновляем ссылки родителя
  if (parent) {
    if (is_left) {
      parent->left_ = child;
    } else {
      parent->right_ = child;
    }
  } else {
    root_ = child;  // Удаляемый узел был корнем
    if (root_) node_to_black(root_);
  }

  if (need_to_balance && child && is_node_red(child)) {
    node_to_black(child);
    need_to_balance = false;
  }

  delete node;
  node = nullptr;

  if (need_to_balance) {
    balance_tree_fix_remove(parent, is_left);  // Передаем родителя и сторону
  }
}

// -------------------- если key_value НЕ const ------------------------

// template <typename Key_, typename T_>
// void BinaryTree<Key_, T_>::remove_node_with_two_child(node_ *&node) {
//     node_ *min_node = find_min_node_from_current(node->right_);
//     node_ *min_parent = min_node->parent_;

//     bool is_min_left = (min_parent != nullptr) && is_left_child(min_node);
//     bool need_to_balance = is_node_black(min_node);

//     node->data_ = min_node->data_;

//     node_ *min_right = min_node->right_;
//     if (min_parent) {
//         if (is_min_left) {
//             min_parent->left_ = min_right;
//         } else {
//             min_parent->right_ = min_right;
//         }
//     }

//     if (node->right_ == min_node) {
//     node->right_ = min_right;
//     }

//     if (min_right) {
//         min_right->parent_ = min_parent;
//         if (need_to_balance && is_node_red(min_right)) {
//             node_to_black(min_right);
//             need_to_balance = false;
//         }
//     }

//     delete min_node;

//     if (need_to_balance && min_parent) {
//         balance_tree_fix_remove(min_parent, is_min_left);
//     }
// }

// -------------------- если key_value НЕ const ------------------------ ^

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::remove_node_with_two_child(node_ *&node) {
  node_ *min_node = find_min_node_from_current(node->right_);
  node_ *min_parent = min_node->parent_;
  node_ *min_right = min_node->right_;

  bool is_min_left = (min_parent != nullptr) && is_left_child(min_node);
  bool need_to_balance = is_node_black(min_node);

  // обновляем указатели у родительского узла min_node
  if (min_parent) {
    if (is_min_left) {
      min_parent->left_ = min_right;
    } else {
      min_parent->right_ = min_right;
    }
  }

  if (min_right) {
    min_right->parent_ = min_parent;
    if (need_to_balance && is_node_red(min_right)) {
      node_to_black(min_right);
      need_to_balance = false;
    }
  }

  // переносим min_node на место node
  min_node->left_ = node->left_;
  min_node->right_ = (node->right_ == min_node) ? min_right : node->right_;
  min_node->parent_ = node->parent_;
  min_node->color_ = node->color_;

  min_node->right_ = (node->right_ == min_node) ? min_right : node->right_;

  if (node->left_) {
    node->left_->parent_ = min_node;
  }

  if (node->right_ && node->right_ != min_node) {
    node->right_->parent_ = min_node;
  }
  if (node->parent_) {
    if (is_left_child(node)) {
      node->parent_->left_ = min_node;
    } else {
      node->parent_->right_ = min_node;
    }
  } else {
    root_ = min_node;
  }

  if (node == min_parent) min_parent = min_node;

  node->left_ = nullptr;
  node->right_ = nullptr;
  node->parent_ = nullptr;

  delete node;
  node = nullptr;

  if (need_to_balance && min_parent) {
    balance_tree_fix_remove(min_parent, is_min_left);
  }
}

// parent - родитель удаленного узла
// is_deleted_left - был ли удаленный узел левым ребенком
template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::balance_tree_fix_remove(node_ *parent,
                                                   bool is_deleted_left) {
  node_ *sibling = nullptr;
  while (parent != nullptr) {
    sibling = is_deleted_left ? parent->right_ : parent->left_;
    // случай 2: брат удаленного узла красный
    if (sibling && is_node_red(sibling)) {
      node_to_black(sibling);
      node_to_red(parent);
      if (is_deleted_left) {
        rotate_left(parent);
        sibling = parent->right_;
      } else {
        rotate_right(parent);
        sibling = parent->left_;
      }
      continue;
    }
    // случай 3: брат удаленного узла черный и дети брата черные
    if (is_node_black(sibling) && children_of_sibling_are_black(sibling)) {
      if (sibling) node_to_red(sibling);
      if (is_node_red(parent)) {
        node_to_black(parent);
        break;
      } else {
        if (parent->parent_) {
          is_deleted_left = (parent == parent->parent_->left_);
        } else {
          break;
        }
        parent = parent->parent_;
        continue;
      }
    }
    // случай 4: брат черный, ближний племянник красный
    // если удаленный узел был левым
    if (sibling && is_deleted_left && is_node_black(sibling->right_) &&
        is_node_red(sibling->left_)) {
      node_to_black(sibling->left_);
      node_to_red(sibling);
      rotate_right(sibling);
      sibling = parent->right_;
    }
    // случай 4, но удаленный был правым
    else if (sibling && !is_deleted_left && is_node_black(sibling->left_) &&
             is_node_red(sibling->right_)) {
      node_to_black(sibling->right_);
      node_to_red(sibling);
      rotate_left(sibling);
      sibling = parent->left_;
    }
    // случай 5: брат черный, дальний племянник красный
    if (sibling && is_deleted_left) {
      if (is_node_red(sibling->right_)) {
        sibling->color_ = parent->color_;
        node_to_black(parent);
        node_to_black(sibling->right_);
        rotate_left(parent);
        // parent = nullptr;  // Завершаем цикл
      }
    } else if (sibling &&
               !is_deleted_left) {  // если удаленный был правым, случай 5
      if (is_node_red(sibling->left_)) {
        sibling->color_ = parent->color_;
        node_to_black(parent);
        node_to_black(sibling->left_);
        rotate_right(parent);
        // parent = nullptr;
      }
    }
    break;
  }
  if (root_) {
    node_to_black(root_);
  }
}

// ---                      вспомогательные                                 ---
// ---                                                                      ---

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::clear_subtree(node_ *current) {
  // да просто налево направо ходим фигачим всех
  if (current != nullptr) {
    clear_subtree(current->left_);
    clear_subtree(current->right_);
    delete current;
    current = nullptr;
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::rotate_left(node_ *node) {
  if (node && node->right_) {
    node_ *new_root = node->right_;

    // Перемещаем правого ребенка на место текущего узла
    node->right_ = new_root->left_;
    if (new_root->left_ != nullptr) new_root->left_->parent_ = node;

    // Обновляем родительский указатель нового корня
    new_root->parent_ = node->parent_;

    // Если узел был корнем дерева, обновляем root
    if (node->parent_ == nullptr) {
      root_ = new_root;
    } else if (is_left_child(node)) {
      node->parent_->left_ = new_root;
    } else if (is_right_child(node)) {
      node->parent_->right_ = new_root;
    }

    // Теперь текущий узел становится левым потомком нового корня
    new_root->left_ = node;
    node->parent_ = new_root;
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::rotate_right(node_ *node) {
  if (node && node->left_) {
    node_ *new_root = node->left_;

    node->left_ = new_root->right_;
    if (new_root->right_ != nullptr) new_root->right_->parent_ = node;

    new_root->parent_ = node->parent_;
    if (!has_node_parent(node)) {
      root_ = new_root;
    } else if (is_left_child(node)) {
      node->parent_->left_ = new_root;
    } else if (is_right_child(node)) {
      node->parent_->right_ = new_root;
    }

    new_root->right_ = node;
    node->parent_ = new_root;
  }
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::nulling_data() {
  root_ = nullptr;
  size_ = 0;
}

// ---                                                       ---
// ---                                                       ---

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *
BinaryTree<Key_, T_>::find_min_node_from_current(node_ *node) const {
  if (node == nullptr) return nullptr;
  node_ *it = node;
  while (it->left_ != nullptr) {
    it = it->left_;
  }
  return it;
}

template <typename Key_, typename T_>
typename BinaryTree<Key_, T_>::node_ *
BinaryTree<Key_, T_>::find_max_node_from_current(node_ *node) const {
  if (node == nullptr) return nullptr;
  node_ *it = node;
  while (it->right_ != nullptr) {
    it = it->right_;
  }
  return it;
}

// ---                 тем более вспомогательные...                         ---
// ---                                                                      ---

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::node_to_red(node_ *&node) {
  if (node)
    node->color_ = node_::Color::RED;
  else
    throw std::out_of_range("node_to_red(): node is nullptr");
}

template <typename Key_, typename T_>
void BinaryTree<Key_, T_>::node_to_black(node_ *&node) {
  if (node) {
    node->color_ = node_::Color::BLACK;
  } else {
    throw std::out_of_range("node_to_black(): node is nullptr");
  }
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_left_child(const node_ *current_node) const {
  // exception is nullptr current_node
  return current_node && current_node->parent_ &&
         current_node == current_node->parent_->left_;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_right_child(const node_ *current_node) const {
  // exception is nullptr current_node
  return current_node && current_node->parent_ &&
         current_node == current_node->parent_->right_;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_parent_left_child(
    const node_ *current_node) const {
  // exception is nullptr current_node
  return current_node->parent_ && current_node->parent_->parent_ &&
         current_node->parent_ == current_node->parent_->parent_->left_;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_parent_right_child(
    const node_ *current_node) const {
  // exception is nullptr current_node
  return current_node->parent_ && current_node->parent_->parent_ &&
         current_node->parent_ == current_node->parent_->parent_->right_;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::has_node_parent(const node_ *current_node) const {
  // exception is nullptr current_node
  return current_node->parent_ != nullptr;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::has_node_both_children(const node_ *node) const {
  return (node->left_ != nullptr && node->right_ != nullptr);
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::has_only_one_child(const node_ *current_node) const {
  // exception is nullptr current_node
  return (has_only_left_child(current_node) ||
          has_only_right_child(current_node));
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::has_only_right_child(
    const node_ *current_node) const {
  return (current_node->right_ != nullptr && current_node->left_ == nullptr);
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::has_only_left_child(
    const node_ *current_node) const {
  return (current_node->right_ == nullptr && current_node->left_ != nullptr);
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::children_of_sibling_are_black(
    const node_ *sibling) const {
  return sibling && (!sibling->left_ || is_node_black(sibling->left_)) &&
         (!sibling->right_ || is_node_black(sibling->right_));
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_node_black(const node_ *node) const {
  if (node) {
    return node->color_ == node_::Color::BLACK;
  } else
    return true;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_node_red(const node_ *node) const {
  if (node) {
    return node->color_ == node_::Color::RED;
  } else {
    return false;
  }
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_root_black() {
  if (!empty()) {
    return is_node_black(root_);
  } else
    throw std::out_of_range("is_root_black(): There is no root, tree is empty");
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::is_black_count_ok() {
  if (empty()) throw std::out_of_range("is_black_count_ok(): Tree is empty");

  int expected_black = -1;
  return check_black_count(root_, 0, expected_black);
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::check_black_count(node_ *node, int current,
                                             int &expected) {
  if (!node) {
    if (expected == -1) {
      expected = current;
      return true;
    }
    return current == expected;
  }

  int new_current = current;
  if (is_node_black(node)) {
    new_current++;
  }

  bool left_ok = check_black_count(node->left_, new_current, expected);
  bool right_ok = check_black_count(node->right_, new_current, expected);
  return left_ok && right_ok;
}

template <typename Key_, typename T_>
bool BinaryTree<Key_, T_>::check_red_red(node_ *node) {
  if (!node) return true;
  bool current_ok =
      !(is_node_red(node) && ((node->left_ && is_node_red(node->left_)) ||
                              (node->right_ && is_node_red(node->right_))));
  return current_ok && check_red_red(node->left_) &&
         check_red_red(node->right_);
}

}  // namespace s21