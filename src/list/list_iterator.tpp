#include "s21_list.h"

namespace s21 {

template <typename T_>
list<T_>::ListIterator::ListIterator(node_* ptr, const list<T_>* parent_list) {
  ptr_ = ptr;
  parent_list_ = parent_list;
}

template <typename T_>
list<T_>::ListIterator::ListIterator(const ListIterator& other) {
  ptr_ = other.ptr_;
}

template <typename T_>
typename list<T_>::ListIterator& list<T_>::ListIterator::operator=(
    const ListIterator& other) {
  if (this != &other) ptr_ = other.ptr_;
  return *this;
}

template <typename T_>
typename list<T_>::reference list<T_>::ListIterator::operator*() {
  if (ptr_ == nullptr) {
    throw std::out_of_range("operator*(): ptr_ is nullptr");
  }
  return ptr_->data_;
}

template <typename T_>
typename list<T_>::ListIterator list<T_>::ListIterator::operator+(int n) const {
  iterator temp = *this;
  for (int i = 0; i < n; i++) {
    if (temp.ptr_->next_ == nullptr) {
      throw std::out_of_range(
          "operator+(int n): it is the last node, next is nullptr");
    }
    ++temp;
  }
  return temp;
}

template <typename T_>
typename list<T_>::ListIterator list<T_>::ListIterator::operator-(int n) const {
  iterator temp = *this;
  for (int i = 0; i < n; i++) {
    if (temp.ptr_->prev_ == nullptr) {
      throw std::out_of_range(
          "operator+(int n): it is the last node, next is nullptr");
    }
    --temp;
  }
  return temp;
}

template <typename T_>
typename list<T_>::ListIterator& list<T_>::ListIterator::operator++() {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator++(): current iterator is nullptr");
  ptr_ = ptr_->next_;
  return *this;
}

template <typename T_>
typename list<T_>::ListIterator list<T_>::ListIterator::operator++(int) {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator++(int): current iterator is nullptr");
  ListIterator temp = *this;
  ptr_ = ptr_->next_;
  return temp;
}

template <typename T_>
typename list<T_>::ListIterator& list<T_>::ListIterator::operator--() {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator--(): current iterator is nullptr");
  ptr_ = ptr_->prev_;
  return *this;
}

template <typename T_>
typename list<T_>::ListIterator list<T_>::ListIterator::operator--(int) {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator--(int): current iterator is nullptr");
  ListIterator temp = *this;
  ptr_ = ptr_->prev_;
  return temp;
}

template <typename T_>
bool list<T_>::ListIterator::operator==(const ListIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T_>
bool list<T_>::ListIterator::operator!=(const ListIterator& other) const {
  return ptr_ != other.ptr_;
}
}  // namespace s21