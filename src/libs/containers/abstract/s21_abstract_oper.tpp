namespace s21 {

template <typename value_type>
bool Abstract<value_type>::ConstIterator::operator!=(
    const ConstIterator &other) const {
  return this->data_ != other.data_;
}

template <typename value_type>
bool Abstract<value_type>::ConstIterator::operator==(
    const ConstIterator &other) const {
  return this->data_ == other.data_;
}

template <typename value_type>
typename Abstract<value_type>::ConstIterator
Abstract<value_type>::ConstIterator::operator+(const size_t value) {
  ConstIterator it_const(this->data_ + value);
  return it_const;
}

template <typename value_type>
typename Abstract<value_type>::ConstIterator &
Abstract<value_type>::ConstIterator::operator++() {
  this->data_++;
  return *this;
}

template <typename value_type>
typename Abstract<value_type>::ConstIterator
Abstract<value_type>::ConstIterator::operator++(int) {
  const_iterator temp(*this);
  this->data_++;
  return temp;
}

template <typename value_type>
typename Abstract<value_type>::ConstIterator &
Abstract<value_type>::ConstIterator::operator--() {
  this->data_--;
  return *this;
}

template <typename value_type>
typename Abstract<value_type>::ConstIterator
Abstract<value_type>::ConstIterator::operator--(int) {
  const_iterator temp(*this);
  this->data_--;
  return temp;
}

template <typename value_type>
typename Abstract<value_type>::Iterator
Abstract<value_type>::Iterator::operator+(const size_type value) {
  iterator iter(this->data_ + value);
  return iter;
}

template <typename value_type>
typename Abstract<value_type>::Iterator
Abstract<value_type>::Iterator::operator-(const size_type value) {
  iterator iter(this->data_ - value);
  return iter;
}

template <typename value_type>
typename Abstract<value_type>::Iterator
Abstract<value_type>::Iterator::operator-(const Iterator &value) {
  iterator iter(this->data_ - value);
  return iter;
}

template <class value_type>
typename Abstract<value_type>::const_reference
Abstract<value_type>::ConstIterator::operator*() {
  if (this->data_ == nullptr) throw std::invalid_argument("bad container");
  return *this->data_;
}

template <typename value_type>
typename Abstract<value_type>::reference
Abstract<value_type>::Iterator::operator*() {
  if (this->data_ == nullptr) throw std::invalid_argument("bad container");
  return *this->data_;
}

template <typename value_type>
typename Abstract<value_type>::Iterator &
Abstract<value_type>::Iterator::operator=(const value_type &value) {
  *this->data_ = value;
  return *this->data_;
}

}  // namespace s21