/* Здесь хранятся тела функций доступа */

namespace s21 {

template <typename value_type>
typename Vector<value_type>::reference Vector<value_type>::at(size_type pos) {
  if (pos >= this->abs_size_)
    throw std::out_of_range("trying to access beyond know elements");
  return this->container_[pos];
}

template <typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::front() {
  if (this->empty()) throw std::out_of_range("empty vector");
  return this->at(0);
}

template <typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::back() {
  if (this->empty()) throw std::out_of_range("empty vector");
  return this->at(this->abs_size_ - 1);
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::data() {
  return this->container_;
}

template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::max_size()
    const noexcept {
  char bits = 63;
  if (sizeof(void*) == 4) bits = 31;
  return (static_cast<size_type>(pow(2, bits)) / sizeof(value_type)) - 1;
}

template <typename value_type>
typename Vector<value_type>::reference Vector<value_type>::operator[](
    size_type pos) {
  return this->at(pos);
}

}  // namespace s21