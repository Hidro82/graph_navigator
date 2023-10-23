/* Здесь хранятся тела функций доступа */

namespace s21 {

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= this->abs_size_)
    throw std::out_of_range("trying to access beyond know elements");
  return this->container_[pos];
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  if (this->empty()) throw std::out_of_range("empty Array");
  return this->at(0);
}

template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  if (this->empty()) throw std::out_of_range("empty Array");
  return this->at(this->abs_size_ - 1);
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return this->begin();
}

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return this->at(pos);
}

}  // namespace s21