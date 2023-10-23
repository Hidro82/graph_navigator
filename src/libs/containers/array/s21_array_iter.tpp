namespace s21 {

template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) {
  if (this != &a) {
    std::move(a.container_, a.container_ + capacity_, this->container_);
  }
  return *this;
}

template <class T, size_t N>
void Array<T, N>::swap(Array &other) {
  std::swap(this->container_, other.container_);
}

template <class T, size_t N>
void Array<T, N>::fill(const_reference value_type) {
  for (size_type i = 0; i < this->abs_size_; i++) {
    this->container_[i] = value_type;
  }
}

template <class T, size_t N>
void Array<T, N>::zero_doer() {
  if (this->capacity_ < 0) throw std::invalid_argument("wrong size mafaka");
  this->abs_size_ = capacity_;
  this->fill(value_type(0));
}

}  // namespace s21