#include "s21_list.h"

namespace s21 {

template <typename T_>
list<T_>::ListConstIterator::ListConstIterator(const node_ *ptr,
                                               const list<T_> *parent_list) {
  ptr_ = ptr;
  parent_list_ = parent_list;
}

template <typename T_>
list<T_>::ListConstIterator::ListConstIterator(const ListConstIterator &other) {
  ptr_ = other.ptr_;
}

template <typename T_>
list<T_>::ListConstIterator::ListConstIterator(const ListIterator &other) {
  ptr_ = other.ptr_;
}

template <typename T_>
typename list<T_>::ListConstIterator &list<T_>::ListConstIterator::operator=(
    const ListConstIterator &other) {
  if (this != &other) ptr_ = other.ptr_;
  return *this;
}

template <typename T_>
typename list<T_>::const_reference list<T_>::ListConstIterator::operator*()
    const {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator*(): const_iterator ptr is nullptr");
  return ptr_->data_;
}

template <typename T_>
typename list<T_>::ListConstIterator list<T_>::ListConstIterator::operator+(
    int n) const {
  const_iterator temp = *this;
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
typename list<T_>::ListConstIterator list<T_>::ListConstIterator::operator-(
    int n) const {
  const_iterator temp = *this;
  for (int i = 0; i < n; i++) {
    if (temp.ptr_->prev_ == nullptr) {
      throw std::out_of_range(
          "operator-(int n): it is first node, next is nullptr");
    }
    --temp;
  }
  return temp;
}

template <typename T_>
typename list<T_>::ListConstIterator &
list<T_>::ListConstIterator::operator++() {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator++(): current iterator is nullptr");
  ptr_ = ptr_->next_;
  return *this;
}

template <typename T_>
typename list<T_>::ListConstIterator list<T_>::ListConstIterator::operator++(
    int) {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator++(int): current iterator is nullptr");
  ListConstIterator temp = *this;
  ptr_ = ptr_->next_;
  return temp;
}

template <typename T_>
typename list<T_>::ListConstIterator &
list<T_>::ListConstIterator::operator--() {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator--(): current iterator is nullptr");
  ptr_ = ptr_->prev_;
  return *this;
}

template <typename T_>
typename list<T_>::ListConstIterator list<T_>::ListConstIterator::operator--(
    int) {
  if (ptr_ == nullptr)
    throw std::out_of_range("operator--(int): current iterator is nullptr");
  ListConstIterator temp = *this;
  ptr_ = ptr_->prev_;
  return temp;
}

template <typename T_>
bool list<T_>::ListConstIterator::operator==(
    const ListConstIterator &other) const {
  return ptr_ == other.ptr_;
}

template <typename T_>
bool list<T_>::ListConstIterator::operator!=(
    const ListConstIterator &other) const {
  return ptr_ != other.ptr_;
}

}  // namespace s21