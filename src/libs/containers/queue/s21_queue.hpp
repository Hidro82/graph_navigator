#include <functional>
#include <initializer_list>
#include <iostream>

using namespace std;

namespace s21 {

template <class T>
class queue {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 public:
  queue() : top_(nullptr), end_(nullptr){};

  queue(initializer_list<value_type> const& items) {
    for (auto& it : items) {
      push(it);
    }
  }

  queue(const queue& q) { copy(q); }

  queue(queue&& q) {
    top_ = std::move(q.top_);
    end_ = std::move(q.end_);
    q.top_ = nullptr;
    q.end_ = nullptr;
  }

  ~queue() {
    while (top_) {
      pop();
    }
  }

  queue& operator=(queue& q) {
    copy(q);
    return *this;
  }

  queue& operator=(queue&& q) {
    top_ = std::move(q.top_);
    end_ = std::move(q.end_);
    q.top_ = nullptr;
    q.end_ = nullptr;
    return *this;
  };

  void push(const_reference val) {
    Node* node = new Node;
    node->val_ = val;
    if (top_ && end_) {
      node->prev_ = end_;
      end_->next_ = node;
      end_ = node;
    } else {
      end_ = node;
      top_ = end_;
    }
  }

  void pop() {
    if (!top_) {
      return;
    }
    Node* tmp = top_;
    top_ = top_->next_;
    delete tmp;
  }

  void swap(queue& other) {
    std::swap(top_, other.top_);
    std::swap(end_, other.end_);
  }

  reference& front() const {
    if (!top_) {
      __throw_underflow_error("queue is empty.");
    }
    return top_->val_;
  }

  reference& back() const {
    if (!end_) {
      __throw_underflow_error("queue is empty.");
    }
    return end_->val_;
  }

  bool empty() const { return top_ ? false : true; }

  size_type size() const {
    size_t sum = 0;
    Node* tmp = nullptr;
    if (top_) {
      tmp = top_;
    }
    while (tmp) {
      ++sum;
      tmp = tmp->next_;
    }
    return sum;
  }

  template <class... Args>
  decltype(auto) emplace(Args&&... args) {
    auto args_list =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto& i : args_list) {
      push(i);
    }
    return back();
  }

 protected:
  void copy(const queue& q) {
    Node* tmp = nullptr;
    if (q.top_) {
      tmp = q.top_;
    }
    while (tmp) {
      push(tmp->val_);
      tmp = tmp->next_;
    }
  }

 private:
  struct Node {
    value_type val_;
    Node* next_{nullptr};
    Node* prev_{nullptr};
    Node(){};
  };

  Node* top_{nullptr};
  Node* end_{nullptr};
};
}  // namespace s21