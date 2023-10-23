/* Здесь хранятся тела функций-конструкторов */

namespace s21 {

template <typename value_type>
Vector<value_type>::Vector() {
  this->zero_doer();
}

template <typename value_type>
Vector<value_type>::Vector(size_type n) {
  this->abs_size_ = n;
  this->capacity_ = n;
  this->container_ = new value_type[n];
}

template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items) {
  this->abs_size_ = items.size();
  this->capacity_ = items.size();
  if (this->abs_size_) {
    this->container_ = new value_type[items.size()];
    std::copy(items.begin(), items.end(), this->container_);
  } else {
    this->zero_doer();
  }
}

template <typename value_type>
Vector<value_type>::Vector(const Vector &v) {
  this->abs_size_ = v.abs_size_;
  this->capacity_ = v.capacity_;
  this->container_ = new value_type[this->capacity_];
  for (size_type i = 0; i < this->abs_size_; i++)
    this->container_[i] = v.container_[i];
}

template <typename value_type>
Vector<value_type>::Vector(Vector &&v) noexcept {
  this->zero_doer();
  std::swap(this->abs_size_, v.abs_size_);
  std::swap(this->capacity_, v.capacity_);
  std::swap(this->container_, v.container_);
}

template <typename value_type>
Vector<value_type>::~Vector() {
  if (this->container_ != nullptr) this->deleter();
}

template <typename value_type>
Vector<value_type> &Vector<value_type>::operator=(Vector &&v) noexcept {
  if (this != &v) {
    if (this->container_ != nullptr) this->deleter();
    std::swap(this->abs_size_, v.abs_size_);
    std::swap(this->capacity_, v.capacity_);
    std::swap(this->container_, v.container_);
  }
  return *this;
}

template <typename value_type>
Vector<value_type> &Vector<value_type>::operator=(const Vector &v) {
  if (this != &v) {
    if (this->container_ != nullptr) this->deleter();
    this->capacity_ = v.capacity_;
    this->abs_size_ = v.abs_size_;
    this->container_ = new value_type[this->capacity_];
    for (size_type i = 0; i < this->abs_size_; i++)
      this->container_[i] = v.container_[i];
  }
  return *this;
}

}  // namespace s21
