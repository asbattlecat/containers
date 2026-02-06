#include "s21_vector.h"

namespace s21 {

// public part:
//____----____----____----____----____----____----____----____----____----____
//----____----____----____----____----____----____----____----____----____----

template <typename T_>
vector<T_>::vector() {
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T_>
vector<T_>::vector(size_type n) : size_(n), capacity_(n) {
  create_data();
}

template <typename T_>
vector<T_>::vector(std::initializer_list<value_type> const& items)
    : size_(items.size()), capacity_(items.size()) {
  create_data();
  std::copy(items.begin(), items.end(), data_);
}

template <typename T_>
vector<T_>::vector(const vector& v) : size_(v.size_), capacity_(v.capacity_) {
  create_data();
  for (size_type i = 0; i != size_; i++) {
    data_[i] = v.data_[i];
  }
}

template <typename T_>
vector<T_>::vector(vector&& v) {
  move_data(std::move(v));
  v.nulling_data();
}

template <typename T_>
vector<T_>::~vector() {
  delete_data();
  nulling_data();
}

template <typename T_>
vector<T_>& vector<T_>::operator=(const vector& v) {
  delete_data();
  size_ = v.size_;
  capacity_ = v.capacity_;
  create_data();
  for (size_type i = 0; i < size_; i++) {
    data_[i] = v.data_[i];
  }
  return *this;
}

template <typename T_>
vector<T_>& vector<T_>::operator=(vector&& v) {
  delete_data();
  move_data(std::move(v));
  v.nulling_data();
  return *this;
}

template <typename T_>
typename vector<T_>::reference vector<T_>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("at(): pos is out of range");
  } else
    return data_[pos];
}

template <typename T_>
typename vector<T_>::reference vector<T_>::operator[](size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("at(): pos is out of range");
  } else
    return data_[pos];
}

template <typename T_>
typename vector<T_>::const_reference vector<T_>::front() {
  if (empty()) throw std::out_of_range("front(): vector is empty");
  return data_[0];
}

template <typename T_>
typename vector<T_>::const_reference vector<T_>::back() {
  if (empty()) throw std::out_of_range("front(): vector is empty");
  return data_[size_ - 1];
}

template <typename T_>
typename vector<T_>::iterator vector<T_>::data() {
  if (empty()) {
    throw std::out_of_range("data(): vector is empty");
  }
  return data_;
}

template <typename T_>
typename vector<T_>::iterator vector<T_>::begin() {
  return data_;
}

template <typename T_>
typename vector<T_>::iterator vector<T_>::end() {
  return data_ + size_;
}

template <typename T_>
bool vector<T_>::empty() const {
  return size_ == 0;
}

template <typename T_>
typename vector<T_>::size_type vector<T_>::size() const {
  return size_;
}

template <typename T_>
typename vector<T_>::size_type vector<T_>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T_>
void vector<T_>::reserve(size_type size) {
  if (size > capacity_) {
    value_type* new_data = new value_type[size]();
    for (size_type i = 0; i < size_; i++) {
      new_data[i] = std::move(data_[i]);
    }
    delete_data();
    data_ = new_data;
    capacity_ = size;
  }
}

template <typename T_>
typename vector<T_>::size_type vector<T_>::capacity() const {
  return capacity_;
}

template <typename T_>
void vector<T_>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type* new_data = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      new_data[i] = std::move(data_[i]);
    }
    delete_data();
    data_ = new_data;
    capacity_ = size_;
  }
}

template <typename T_>
void vector<T_>::clear() {
  if constexpr (!std::is_trivially_destructible<T_>::value) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i].~value_type();
    }
  }
  size_ = 0;
}

template <typename T_>
typename vector<T_>::iterator vector<T_>::insert(iterator pos,
                                                 const_reference value) {
  size_type index = pos - begin();
  check_capacity();
  for (size_type i = size_; i > index; --i) {
    data_[i] = std::move(data_[i - 1]);
  }
  data_[index] = value;
  size_++;
  return begin() + index;
}

template <typename T_>
void vector<T_>::erase(iterator pos) {
  size_type index = pos - begin();
  for (size_type i = index; i < size_ - 1; i++) {
    data_[i] = std::move(data_[i + 1]);
  }
  size_--;
  if constexpr (!std::is_trivially_destructible<T_>::value)
    data_[size_].~value_type();
}

template <typename T_>
void vector<T_>::push_back(const_reference value) {
  check_capacity();
  data_[size_] = value;
  size_++;
}

template <typename T_>
void vector<T_>::pop_back() {
  if constexpr (!std::is_trivially_destructible<T_>::value)
    data_[size_ - 1].~value_type();
  size_--;
}

template <typename T_>
void vector<T_>::swap(vector& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T_>
template <typename... Args>
typename vector<T_>::iterator vector<T_>::insert_many(const_iterator pos,
                                                      Args&&... args) {
  size_type index = pos - begin();
  size_type new_el_size = sizeof...(args);
  while (size_ + new_el_size > capacity_) {
    increase_capacity();
  }

  size_ += new_el_size;
  for (size_type i = size_; i > index + new_el_size; i--) {
    data_[i - 1] = std::move(data_[i - new_el_size - 1]);
  }

  value_type temp[] = {std::forward<Args>(args)...};
  size_type el_cnt = sizeof(temp) / sizeof(temp[0]);
  for (size_type i = 0; i < el_cnt; i++) {
    data_[index++] = temp[i];
  }

  return begin() + index;
}

template <typename T_>
template <typename... Args>
void vector<T_>::insert_many_back(Args&&... args) {
  size_type new_el_size = sizeof...(args);
  while (size_ + new_el_size > capacity_) {
    increase_capacity();
  }
  value_type temp[] = {std::forward<Args>(args)...};

  for (size_type i = 0; i < new_el_size; i++) {
    data_[size_++] = temp[i];
  }
}

// private part:
//____----____----____----____----____----____----____----____----____----____
//----____----____----____----____----____----____----____----____----____----

template <typename T_>
void vector<T_>::delete_data() {
  if (data_) delete[] data_;
}

template <typename T_>
void vector<T_>::create_data() {
  data_ = new value_type[capacity_]();
}

template <typename T_>
void vector<T_>::nulling_data() {
  data_ = nullptr;
  capacity_ = 0;
  size_ = 0;
}

template <typename T_>
void vector<T_>::move_data(vector&& other) {
  data_ = other.data_;
  capacity_ = other.capacity_;
  size_ = other.size_;
}

template <typename T_>
void vector<T_>::check_capacity() {
  if (need_to_increase_capacity()) increase_capacity();
}

template <typename T_>
bool vector<T_>::need_to_increase_capacity() {
  return (size_ == capacity_ ? true : false);
}

template <typename T_>
void vector<T_>::increase_capacity() {
  reserve(capacity_ == 0 ? 1 : capacity_ * 2);
}

}  // namespace s21