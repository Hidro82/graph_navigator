#ifndef SRC_ARRAY_S21_ARRAY_H
#define SRC_ARRAY_S21_ARRAY_H
#include <initializer_list>

/* Array - это классическая реализация статического массива. Поля - тело
  массива и его размер */

namespace s21 {
template <class T, size_t N>
class Array : public Abstract<T> {
 public:
  using pointer = typename Abstract<T>::pointer;
  using value_type = typename Abstract<T>::value_type;
  using reference = typename Abstract<T>::reference;
  using const_reference = typename Abstract<T>::const_reference;
  using iterator = typename Abstract<T>::Iterator;
  using const_iterator = typename Abstract<T>::ConstIterator;
  using size_type = typename Abstract<T>::size_type;

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);
  ~Array() { fill(0); };

  Array &operator=(Array &&a);

  /* Общие методы доступа к полям контейнеров по индексу, началу и концу */

  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  reference at(size_type pos);
  iterator data();
  size_type max_size() {
    return this->capacity_;
  };  // максимально возможное кол-во элементов
  iterator begin() {
    return iterator(this->container_);
  };  // возврат итератора на первый элемент
  iterator end() {
    return iterator(this->container_ + this->abs_size_);
  };  // и, наоборот, на последний

  void swap(Array &other);
  void fill(const_reference value);

 private:
  size_type capacity_ = N;
  value_type container_[N];
  void zero_doer();
};

}  // namespace s21

#include "s21_array_access.tpp"
#include "s21_array_constr.tpp"
#include "s21_array_iter.tpp"

#endif  // SRC_ARRAY_S21_ARRAY_H