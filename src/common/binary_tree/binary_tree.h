#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <map>
#include <type_traits>
#include <utility>

namespace s21 {

template <typename Key_, typename T_>
class map;

template <typename Key_>
class set;

/*
Класс BinaryTree используется для класса map и set, как основа. здесь описаны
основные методы, которые являются общими для map и set
*/

template <typename Key_, typename T_>
class BinaryTree {
  friend class map<Key_, T_>;
  friend class set<Key_>;
  friend class iterator;
  friend class const_iterator;

 public:
  using key_type = Key_;
  using mapped_type = T_;
  // если T_ - void, то создается переназначение key_type, а если нет, то просто
  // pair из const Key_ и T_
  using value_type = typename std::conditional<std::is_void_v<T_>, Key_,
                                               std::pair<const Key_, T_>>::type;

  using reference = value_type &;
  using const_reference = const value_type &;

  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;

 protected:
  struct node_ {
    value_type data_;
    node_ *parent_;
    node_ *left_;
    node_ *right_;
    enum Color { RED, BLACK } color_;
    bool operator<(const node_ &other) const;
    bool operator>(const node_ &other) const;
    bool operator!=(const node_ &other) const;
    bool operator==(const node_ &other) const;
  };
  node_ *root_;
  size_type size_;

 public:
  class iterator;
  class const_iterator;

  BinaryTree();
  BinaryTree(std::initializer_list<value_type> const &items);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other);
  ~BinaryTree();
  BinaryTree &operator=(const BinaryTree &other);
  BinaryTree operator=(BinaryTree &&other);

  void insert(const value_type &value);
  void remove_node(iterator pos);

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();

  bool contains(const key_type &key);

  iterator find_node_iterator(const key_type &needed);
  node_ *find_node_node_(const key_type &needed);
  node_ *get_node(iterator it);
  // функция для проверки сбалансированности дерева
  bool is_balanced();

  node_ *find_max_node() const;
  node_ *find_min_node() const;
  bool is_there_such_node(const key_type &key);

  // internal classes
  // ----------------------------------------------------------------------------
  class iterator {
    friend class BinaryTree<Key_, T_>;
    friend class map<Key_, T_>;

    //  protected:
    node_ *current_;
    BinaryTree &tree_;

   public:
    iterator(node_ *node, BinaryTree &tree);
    iterator &operator=(const iterator &other);
    iterator(const iterator &other);
    reference operator*();
    const_reference operator*() const;
    pointer operator->();
    const_pointer operator->() const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;

   private:
    void move_to_bigger_key_iterator();
    void move_to_smaller_key_iterator();
  };

  class const_iterator {
    friend class BinaryTree<Key_, T_>;
    friend class map<Key_, T_>;

    const node_ *current_;
    const BinaryTree &tree_;

   public:
    const_iterator(const node_ *node, const BinaryTree &tree);
    const_iterator(const const_iterator &other);
    const_iterator &operator=(const const_iterator &other);
    const_reference operator*();
    const_pointer operator->();
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;

   private:
    void move_to_bigger_key_const_iter();
    void move_to_smaller_key_const_iter();
  };

  // ----------------------------------------------------------------------------

 private:
  node_ *copy_tree(node_ *origin_node, node_ *parent);

  void insert_node(node_ *new_node);
  void balance_tree_fix_insert(node_ *node);

  void remove_node_with_no_children(node_ *&node);
  void remove_node_with_one_child(node_ *&node);
  void remove_node_with_two_child(node_ *&node);
  void balance_tree_fix_remove(node_ *node, bool is_left);

  void clear_subtree(node_ *node);
  void rotate_left(node_ *node);
  void rotate_right(node_ *node);
  void nulling_data();

  node_ *find_min_node_from_current(node_ *node) const;
  node_ *find_max_node_from_current(node_ *node) const;

  void node_to_red(node_ *&node);
  void node_to_black(node_ *&node);

  bool is_left_child(const node_ *current_node) const;
  bool is_right_child(const node_ *current_node) const;
  bool is_parent_left_child(const node_ *current_node) const;
  bool is_parent_right_child(const node_ *current_node) const;
  bool has_node_parent(const node_ *current_node) const;
  bool has_node_both_children(const node_ *current_node) const;
  bool has_only_one_child(const node_ *current_node) const;
  bool has_only_left_child(const node_ *current_node) const;
  bool has_only_right_child(const node_ *current_node) const;

  bool children_of_sibling_are_black(const node_ *sibling) const;

  bool is_node_black(const node_ *node) const;
  bool is_node_red(const node_ *node) const;
  bool is_root_black();
  bool is_black_count_ok();
  bool check_black_count(node_ *node, int current, int &expected);
  bool check_red_red(node_ *node);
};
}  // namespace s21

#include "binary_tree.tpp"
#include "binary_tree_private.tpp"
#include "const_iterator.tpp"
#include "iterator.tpp"
#include "node.tpp"

#endif