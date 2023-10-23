namespace s21 {

template <class T, size_t N>
Array<T, N>::Array() {
  this->zero_doer();
}

template <class T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  this->zero_doer();
  if (items.size() > capacity_) {
    throw std::out_of_range("too many initializers");
  }
  int count = 0;
  for (auto element : items) {
    this->container_[count] = element;
    ++count;
  }
}

template <class T, size_t N>
Array<T, N>::Array(const Array &a) {
  this->zero_doer();
  for (size_type i = 0; i < this->abs_size_; ++i)
    this->container_[i] = a.container_[i];
}

template <class T, size_t N>
Array<T, N>::Array(Array &&a) {
  this->zero_doer();
  if (this != &a) {
    std::move(a.container_, a.container_ + capacity_, this->container_);
  }
}

}  // namespace s21