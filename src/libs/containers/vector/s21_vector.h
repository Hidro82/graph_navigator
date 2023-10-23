#ifndef SRC_VECTOR_S21_VECTOR_H_
#define SRC_VECTOR_S21_VECTOR_H_

#include <cmath>
#include <iostream>

#include "../abstract/s21_abstract.h"

namespace s21 {

template <typename T>  // Объявление шаблона с параметром template T
class Vector : public Abstract<T> {
 public:
  /* Внутриклассовые переопределения для удобства восприятия кода
      {по версии индусов-авторов оригинала} */
  using pointer = typename Abstract<T>::pointer;  // задаём указатель
  using value_type = typename Abstract<T>::value_type;  // меняем имя параметра
  using reference = typename Abstract<T>::reference;  // имя ссылки на параметр
  using const_reference =
      typename Abstract<T>::const_reference;  // и даже постоянной ссылки на
                                              // параметр
  using iterator =
      typename Abstract<T>::Iterator;  // указатель на элемент вектора
  using const_iterator = typename Abstract<T>::ConstIterator;  // nuff said
  using size_type = typename Abstract<T>::size_type;  // размер вектора

  /* Сюда мы пихаем конструкторы класса */
  Vector();  // стандартный конструктор, создаёт пустой вектор
  Vector(size_type n);  // этот конструктор создаёт вектор определённого размера
  Vector(
      std::initializer_list<value_type> const &items);  // этот - инициализирует
  Vector(const Vector &v);      // копирование
  Vector(Vector &&v) noexcept;  // перенос
  ~Vector();  // дестракшн, павер, мотивейшен
  Vector &operator=(
      Vector &&v) noexcept;  // перегрузка оператора равенства для переноса
  Vector &operator=(const Vector &v);  // и для копирования

  /* Публичные методы доступа к информации о заполнении контейнера */

  void reserve(size_type size) {
    if (size > this->abs_size_) this->mem_resize(size);
  };  // создать новый контейнер размера size и
      // скопировать в него текущий массив
  void shrink_to_fit();  // уменьшение занятой памяти путём освобождения
                         // неиспользованных элементов
  size_type capacity() {
    return this->capacity_;
  };  // количество памяти в массиве

  /* Публичные методы для изменения контейнера */
  void clear();  // очистить контейнер
  iterator insert(iterator pos,
                  const_reference value);  // поместить элемент в определённое
                                           // место и вернуть указатель
  void erase(iterator pos);  // очистить элемент в pos
  void push_back(const_reference value);  // добавить элемент в конец массива
  void pop_back() {
    this->abs_size_ > 0 ? this->abs_size_-- : 0;
  };                         // убрать последний элемент
  void swap(Vector &other);  // свапнуть содержимое двух контейнеров

  /* Общие методы доступа к полям контейнеров по индексу, началу и концу */

  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  reference at(size_type pos);
  iterator data();
  size_type max_size()
      const noexcept;  // максимально возможное кол-во элементов
  iterator begin() {
    iterator iter(this->container_);
    return iter;
  };  // возврат итератора на первый элемент
  iterator end() {
    iterator iter(this->container_ + this->abs_size_);
    return iter;
  };  // и, наоборот, на последний

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

  void push_back_stack(const_reference value);

 private:
  /* Соб-сна, тело контейнера */
  size_type capacity_;  // размер буффера (занимаемая память)
  value_type *container_;  // хранимый массив

  /* Подковёрная грязь для реализации (работа с памятью) */
  void zero_doer();  // присваиватель пустого вектора
  void deleter();
  void mem_resize(size_type size);  // перераспределение памяти
};

}  // namespace s21

/* Включение файлов с телами функций. Шаблонные методы работают несколько иначе,
  чем методы в классическом представлении. При сборке компиллятор не нуждается
  в исходниках шаблонов, ему достаточно ссылок. */

#include "s21_vector_access.tpp"
#include "s21_vector_constr.tpp"
#include "s21_vector_iter.tpp"
#include "s21_vector_off.tpp"

#endif  // SRC_V_S21_VECTOR_H_