#ifndef SRC_ABSTRACT_S21_ABSTRACT_H_
#define SRC_ABSTRACT_S21_ABSTRACT_H_
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

/* Abstract представляет из себя служебный виртуальный класс, хранящий
  в себе всё, что нужно для итерирования в Vector и Array */

namespace s21 {
template <typename T>
class Abstract {
 public:
  /* Поскольку переопределения в Array и Vector идентично, то удобно их объявить
    в теле данного класса, а после - давать ссылку */

  using pointer = T *;
  using const_pointer = const T *;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /* Класс ConstIterator представляет из себя итератор с произвольным доступом в
    поля итерируемого класса без возможности редактирования содержимого.
    Доступ осуществляется путём перегруженных операторов. */

  class ConstIterator {
   public:
    ConstIterator() { this->data_ = nullptr; };
    ConstIterator(pointer pt) { this->data_ = pt; };
    ConstIterator(const ConstIterator &other) : data_(other.data_) {}
    ~ConstIterator(){};

    ConstIterator &operator=(const ConstIterator &other) {
      this->data_ = other.data_;
      return *this;
    };
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    operator const_pointer() { return this->data_; }
    const_reference operator*();
    ConstIterator operator+(const size_t value);
    bool operator!=(const ConstIterator &other) const;
    bool operator==(const ConstIterator &other) const;

    /* Поскольку классы Vector и Array, по-сути, дочерние по отношению к
      Abstract, то необходимо объявлять все приватные поля как защищённые, чтобы
      при наследовании у Vector и Array был к ним доступ */

   protected:
    pointer data_;
  };

  /* Класс Iterator дочерний по отношению к ConstIterator, следовательно,
    наследует все его методы. Также он содержит в себе новые перегрузки,
    предназначенные для редактирования содержимого Vector и Array */

  class Iterator : public ConstIterator {
   public:
    Iterator() : ConstIterator(){};
    Iterator(pointer pt) : ConstIterator(pt){};
    Iterator(const Iterator &other) : ConstIterator(other) {}
    Iterator(const ConstIterator &other) : ConstIterator(other) {}
    ~Iterator() {}
    reference operator*();
    Iterator &operator=(const Iterator &other) {
      this->data_ = other.data_;
      return *this;
    }
    Iterator &operator=(const value_type &value);
    operator pointer() { return this->data_; }
    Iterator operator+(const size_t value);
    Iterator operator-(const size_t value);
    Iterator operator-(const Iterator &value);
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  /* Публичные методы для итерирования по элементам */

  virtual bool empty() const noexcept {
    return (this->abs_size_ == 0);
  };  // проверка на пустой вектор
  virtual size_type size() const noexcept {
    return this->abs_size_;
  };  // кол-во элементов

 protected:
  Abstract(){};
  size_t abs_size_;
};

}  // namespace s21

#include "s21_abstract_oper.tpp"

#endif  // SRC_ABSTRACT_S21_ABSTRACT_H_