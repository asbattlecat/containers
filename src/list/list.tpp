#include "s21_list.h"

namespace s21 {

// public part of list
// *--------------------------------------------------------------------------*
// *--------------------------------------------------------------------------*

template <typename T_>
list<T_>::list() {
  nulling_head_tail();
  size_ = 0;
}

template <typename T_>
list<T_>::list(size_type n) {
  nulling_head_tail();
  size_ = n;
  create_list();
}

template <typename T_>
list<T_>::list(std::initializer_list<value_type> const &items)
    : size_(items.size()) {
  nulling_head_tail();
  create_list();
  iterator current = begin();
  for (const auto &item : items) {
    if (current == end()) break;
    *current = item;
    ++current;
  }
}

template <typename T_>
list<T_>::list(const list &l) : size_(l.size_) {
  nulling_head_tail();
  create_list();
  const_iterator l_it = l.begin();
  for (iterator it = begin(); it != end(); ++it, ++l_it) {
    *it = *l_it;
  }
}

template <typename T_>
list<T_>::list(list &&l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.nulling_head_tail();
  l.size_ = 0;
}

template <typename T_>
list<T_>::~list() {
  clear();
}

template <typename T_>
list<T_> &list<T_>::operator=(list &&l) {
  if (this != &l) {
    clear();
    size_ = l.size_;
    head_ = l.head_;
    tail_ = l.tail_;
    l.nulling_head_tail();
    l.size_ = 0;
  }
  return *this;
}

template <typename T_>
typename list<T_>::const_reference list<T_>::front() const {
  if (empty()) throw std::out_of_range("front(): list is empty");
  return head_->data_;
}

template <typename T_>
typename list<T_>::const_reference list<T_>::back() const {
  if (empty()) throw std::out_of_range("back(): list is empty");
  return tail_->data_;
}

template <typename T_>
typename list<T_>::iterator list<T_>::begin() {
  return iterator(head_, this);
}

template <typename T_>
typename list<T_>::iterator list<T_>::end() {
  return iterator(nullptr, this);
}

template <typename T_>
typename list<T_>::const_iterator list<T_>::begin() const {
  return const_iterator(head_, this);
}

template <typename T_>
bool list<T_>::empty() const {
  return size_ == 0;
}

template <typename T_>
typename list<T_>::size_type list<T_>::size() const {
  return size_;
}

template <typename T_>
typename list<T_>::size_type list<T_>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(node_);
}

template <typename T_>
void list<T_>::clear() {
  iterator it = begin();
  while (it != end()) {
    iterator temp = it++;
    delete temp.ptr_;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T_>
typename list<T_>::iterator list<T_>::insert(iterator pos,
                                             const_reference value) {
  node_ *new_node = new node_;
  new_node->data_ = value;
  if (pos.ptr_ == nullptr) {
    new_node->next_ = nullptr;
    new_node->prev_ = tail_;
    if (tail_ != nullptr) tail_->next_ = new_node;
    tail_ = new_node;
    if (head_ == nullptr) head_ = new_node;
  } else {
    new_node->next_ = pos.ptr_;
    new_node->prev_ = pos.ptr_->prev_;
    if (pos.ptr_->prev_ != nullptr) {
      pos.ptr_->prev_->next_ = new_node;
    } else
      head_ = new_node;
    pos.ptr_->prev_ = new_node;
  }
  size_++;
  return iterator(new_node, this);
}

template <typename T_>
void list<T_>::erase(iterator pos) {
  if (pos.ptr_ != nullptr) {
    if (pos.ptr_->prev_ != nullptr && pos.ptr_->next_ != nullptr) {
      pos.ptr_->prev_->next_ = pos.ptr_->next_;
      pos.ptr_->next_->prev_ = pos.ptr_->prev_;
    }
    if (pos.ptr_->prev_ == nullptr) {
      head_ = pos.ptr_->next_;
      if (head_ != nullptr) head_->prev_ = nullptr;
    }
    if (pos.ptr_->next_ == nullptr) {
      tail_ = pos.ptr_->prev_;
      if (tail_ != nullptr) tail_->next_ = nullptr;
    }
    delete pos.ptr_;
    --size_;
  }
}

template <typename T_>
void list<T_>::push_back(const_reference value) {
  node_ *new_node = new node_;
  new_node->data_ = value;
  new_node->next_ = nullptr;
  if (empty()) {
    new_node->prev_ = nullptr;
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T_>
void list<T_>::pop_back() {
  if (!empty()) erase(iterator(tail_, this));
}

template <typename T_>
void list<T_>::push_front(const_reference value) {
  node_ *new_node = new node_;
  new_node->data_ = value;
  new_node->prev_ = nullptr;
  if (empty()) {
    new_node->next_ = nullptr;
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
  }
  ++size_;
}

template <typename T_>
void list<T_>::pop_front() {
  if (!empty()) erase(iterator(head_, this));
}

template <typename T_>
void list<T_>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T_>
void list<T_>::merge(list &other) {
  if (!is_sorted()) sort();
  if (!other.is_sorted()) other.sort();
  iterator it = begin();
  iterator other_it = other.begin();
  while (it != end() && other_it != other.end()) {
    if (it.ptr_->data_ > other_it.ptr_->data_) {
      move_node(it, other_it, other);
    } else {
      ++it;
    }
  }
  while (other_it != other.end()) {
    move_node(end(), other_it, other);
  }
  size_ = size_ + other.size_;
  other.clear();
}

template <typename T_>
void list<T_>::splice(const_iterator pos, list &other) {
  iterator other_it = other.find_iterator(pos);
  while (other_it != other.end()) {
    move_node(end(), other_it, other);
  }
  size_ = node_number(end());
  other.size_ = other.node_number(other.end());
}

template <typename T_>
void list<T_>::reverse() {
  if (!empty()) {
    node_ *current = head_;
    node_ *temp = nullptr;
    while (current != nullptr) {
      temp = current->prev_;
      current->prev_ = current->next_;
      current->next_ = temp;
      current = current->prev_;
    }
    temp = head_;
    head_ = tail_;
    tail_ = temp;
  }
}

template <typename T_>
void list<T_>::sort() {
  bubble_sort();
}

template <typename T_>
void list<T_>::unique() {
  if (!empty()) {
    if (!is_sorted()) sort();
    for (iterator it = begin(); it != end() && it.ptr_->next_ != nullptr;) {
      if (it.ptr_->data_ == it.ptr_->next_->data_) {
        erase(iterator(it.ptr_->next_, this));
      } else
        ++it;
    }
  }
}

template <typename T_>
template <typename... Args>
typename list<T_>::iterator list<T_>::insert_many(const_iterator pos,
                                                  Args &&...args) {
  size_type new_el_size = sizeof...(args);
  value_type temp[] = {std::forward<Args>(args)...};
  iterator it = find_iterator(pos);
  for (long i = (long)new_el_size - 1; i >= 0; i--) {
    it = insert(it, temp[i]);
  }
  return it;
}

template <typename T_>
template <typename... Args>
void list<T_>::insert_many_back(Args &&...args) {
  size_type new_el_size = sizeof...(args);
  value_type temp[] = {std::forward<Args>(args)...};
  for (size_type i = 0; i < new_el_size; i++) {
    insert(end(), temp[i]);
  }
}

template <typename T_>
template <typename... Args>
void list<T_>::insert_many_front(Args &&...args) {
  size_type new_el_size = sizeof...(args);
  value_type temp[] = {std::forward<Args>(args)...};
  for (long i = (long)new_el_size - 1; i >= 0; i--) {
    insert(begin(), temp[i]);
  }
}

// private part of list
// *--------------------------------------------------------------------------*
// *--------------------------------------------------------------------------*

template <typename T_>
void list<T_>::create_list() {
  for (size_type i = 0; i < size_; i++) {
    node_ *new_node = new node_;
    new_node->data_ = T_();
    new_node->next_ = nullptr;
    new_node->prev_ = tail_;
    if (tail_ != nullptr) tail_->next_ = new_node;
    tail_ = new_node;
    if (head_ == nullptr) head_ = new_node;
  }
}

template <typename T_>
void list<T_>::nulling_head_tail() {
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T_>
void list<T_>::bubble_sort() {
  int n = size();
  bool swapped = true;
  for (int i = 0; i < n - 1 && swapped; ++i) {
    swapped = false;
    iterator it = begin();
    for (int j = 0; j < n - i - 1; ++j, ++it) {
      if (it.ptr_->next_ != nullptr && it.ptr_->data_ > it.ptr_->next_->data_) {
        std::swap(it.ptr_->data_, it.ptr_->next_->data_);
        swapped = true;
      }
    }
  }
}

template <typename T_>
bool list<T_>::is_sorted() {
  bool sorted = true;
  for (iterator it = begin(); it.ptr_->next_ != nullptr; ++it) {
    if (it.ptr_->data_ > it.ptr_->next_->data_) sorted = false;
  }
  return sorted;
}

/**
 * @brief перемещает узел (other_it) из одного списка в текущий, на позицию pos.
 */
template <typename T_>
void list<T_>::move_node(iterator pos, iterator &other_it, list &other) {
  node_ *oth_next =
      other_it.ptr_->next_;  // для переключения итератора на next_
  if (other_it.ptr_ != nullptr) {
    // убираем из предыдущего списка
    other.unlink_node(other_it);

    // вставлем в новый список
    if (pos.ptr_ != nullptr) {
      if (pos.ptr_->prev_ == nullptr) {
        other_it.ptr_->prev_ = nullptr;
        other_it.ptr_->next_ = pos.ptr_;
        pos.ptr_->prev_ = other_it.ptr_;
        head_ = other_it.ptr_;
      } else {
        other_it.ptr_->prev_ = pos.ptr_->prev_;
        other_it.ptr_->next_ = pos.ptr_;
        pos.ptr_->prev_->next_ = other_it.ptr_;
        pos.ptr_->prev_ = other_it.ptr_;
      }
    } else {
      tail_->next_ = other_it.ptr_;
      other_it.ptr_->prev_ = tail_;
      tail_ = other_it.ptr_;
    }
    other_it = iterator(oth_next, &other);
  }
}

template <typename T_>
void list<T_>::unlink_node(iterator &pos) {
  if (pos.ptr_->prev_ != nullptr) {
    pos.ptr_->prev_->next_ = pos.ptr_->next_;
  } else {
    head_ = pos.ptr_->next_;
    if (pos.ptr_->next_ != nullptr) {
      pos.ptr_->next_->prev_ = nullptr;
    }
  }
  if (pos.ptr_->next_ != nullptr) {
    pos.ptr_->next_->prev_ = pos.ptr_->prev_;
  } else {
    tail_ = pos.ptr_->prev_;
    if (pos.ptr_->prev_ != nullptr) {
      pos.ptr_->prev_->next_ = nullptr;
    }
  }
}

template <typename T_>
typename list<T_>::iterator list<T_>::find_iterator(const_iterator pos) {
  iterator it = begin();
  while (it != end() && it.ptr_ != pos.ptr_) {
    ++it;
  }
  return it;
}

template <typename T_>
typename list<T_>::size_type list<T_>::node_number(iterator pos) {
  size_type number = 0;
  if (!empty()) {
    for (iterator it = begin(); it.ptr_ != pos.ptr_; ++it) {
      ++number;
    }
  }
  return number;
}

}  // namespace s21
