/* Здесь хранятся тела служебных функций */

namespace s21 {

template <typename value_type>
void Vector<value_type>::zero_doer() {
  this->abs_size_ = 0;
  this->capacity_ = 0;
  this->container_ = nullptr;
}

template <typename value_type>
void Vector<value_type>::deleter() {
  this->abs_size_ = 0;
  this->capacity_ = 0;
  if (this->container_) delete[] this->container_;
  this->container_ = nullptr;
}

template <typename value_type>
void Vector<value_type>::mem_resize(size_type size) {
  if (size < this->abs_size_)
    throw std::out_of_range("trying put bigger in lesser");
  value_type *buff = new value_type[size];
  if (!(buff)) throw std::out_of_range("need memory");
  for (size_type i = 0; i < this->abs_size_; i++) buff[i] = this->container_[i];
  this->capacity_ = size;
  std::swap(this->container_, buff);
  delete[] buff;
}

/* Данная функция, де-факто, костыль, созданный для обхода векторной
  тенданции при push увеличивать контейнер в два раза. Чтобы не захламлять
  описание стека - создана эта функция, увеличивающая всё на один */

template <typename value_type>
void Vector<value_type>::push_back_stack(const_reference value) {
  if (this->abs_size_ == this->capacity_) {
    mem_resize(this->abs_size_ + 1);
  }
  this->container_[this->abs_size_++] = value;
}

}  // namespace s21
