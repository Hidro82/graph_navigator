/* Здесь хранятся тела методов для итерирования */

namespace s21 {

template <typename value_type>
void Vector<value_type>::clear() {
  this->abs_size_ = 0;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type position = &(*pos) - this->container_;
  if (position < 0 || position > this->abs_size_) {
    throw std::out_of_range("index out of range");
  }
  if (this->abs_size_ + 1 >= this->capacity_) {
    this->mem_resize(this->capacity_ * 2);
  }
  value_type buffer_1 = this->container_[position];
  this->abs_size_++;
  this->container_[position] = value;
  for (size_type i = position + 1; i < this->abs_size_; ++i) {
    value_type buffer_2 = this->container_[i];
    this->container_[i] = buffer_1;
    buffer_1 = buffer_2;
  }
  return this->container_ + position;
}

template <typename value_type>
void Vector<value_type>::erase(iterator pos) {
  size_type position = &(*pos) - this->container_;
  size_type zero = 0;
  if (zero > position || position > this->abs_size_) {
    throw std::out_of_range("index out ot range");
  }
  for (size_type i = position + 1; i < this->abs_size_; i++) {
    this->container_[i - 1] = this->container_[i];
  }
  this->abs_size_--;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (this->abs_size_ == this->capacity_) {
    mem_resize(this->abs_size_ * 2);
  }
  this->container_[this->abs_size_++] = value;
}

template <typename value_type>
void Vector<value_type>::swap(Vector& other) {
  std::swap(other.abs_size_, this->abs_size_);
  std::swap(other.capacity_, this->capacity_);
  std::swap(other.container_, this->container_);
}

template <typename value_type>
void Vector<value_type>::shrink_to_fit() {
  if (this->abs_size_ < this->capacity_) {
    this->mem_resize(this->abs_size_);
  }
}

template <typename value_type>
template <typename... Args>
void Vector<value_type>::emplace_back(Args&&... args) {
  auto args_list =
      std::initializer_list<value_type>{std::forward<Args>(args)...};
  for (auto& i : args_list) {
    push_back(i);
  }
}

template <typename value_type>
template <typename... Args>
typename Vector<value_type>::iterator Vector<value_type>::emplace(
    const_iterator pos, Args&&... args) {
  iterator it;
  auto args_list =
      std::initializer_list<value_type>{std::forward<Args>(args)...};

  for (auto& i : args_list) {
    it = insert(pos, i);
  }
  return it;
}

}  // namespace s21