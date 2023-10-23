#ifndef SRC_STACK_S21_STACK_H
#define SRC_STACK_S21_STACK_H
#include "../vector/s21_vector.h"

namespace s21 {

template <class T, class Container = s21::Vector<T>>
class Stack {
 public:
  /* Переопределения. По сути - такие же, как у вектора */

  using pointer = typename Container::pointer;
  using const_pointer = typename Container::const_pointer;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  /* Конструкторы и деструктор. Главной оссобенностью является применение
  функций, уже запиленных в векторе */

  Stack() : con_(){};
  Stack(std::initializer_list<value_type> const &items) : con_(items){};
  Stack(const Stack &s) : con_(s.con_){};
  Stack(Stack &&s) : con_(std::move(s.con_)){};
  ~Stack(){};

  /* Перегрузка требуется только для оператора переноса */

  Stack &operator=(Stack &&s) {
    this->con_ = std::move(s.con_);
    return *this;
  };

  /* Функции для работы со стеком. В реализации своей тоже до ужаса простые */

  const_reference top() { return con_.back(); };
  bool empty() { return con_.empty(); };
  size_type size() { return con_.size(); };
  void push(const_reference value) { this->con_.push_back_stack(value); };
  void pop() { this->con_.pop_back(); };
  void swap(Stack &other) { this->con_.swap(other.con_); };

  template <typename... Args>
  void emplace_front(Args &&...args) {
    this->con_.emplace_back(std::forward<Args>(args)...);
  };

 private:
  Container con_;  // Ну, и сам, соб-но г-ря, стек
};

}  //  namespace s21

#endif  // SRC_STACK_S21_STACK_H