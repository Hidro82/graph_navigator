#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>

class list {
 private:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  struct Node {
    value_type data_;
    Node* next_;
    Node* prev_;
    Node(value_type data = value_type())
        : data_(data), next_(nullptr), prev_(nullptr) {}
  };
  Node* head_;
  Node* tail_;
  Node* end_;
  size_type size_;

  void ChangeEnd() {
    if (end_) {
      end_->next_ = head_;
      end_->prev_ = tail_;
      end_->data_ = size_;
    }
    if (head_) {
      head_->prev_ = end_;
    }
    if (tail_) {
      tail_->next_ = end_;
    }
  }

 public:
  list() : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);
    ChangeEnd();
  }
  list(size_type n) : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);

    if (n > std::numeric_limits<size_type>::max()) {
      throw std::out_of_range("Limit of the container is exceeded");
    }

    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
    ChangeEnd();
  }

  list(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);
    for (const auto& item : items) {
      push_back(item);
    }
  }
  list(const list& l)
      : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);
    {
      Node* tmp = l.head_;
      for (size_type i = 0; i != l.size_; i++) {
        push_back(tmp->data_);
        tmp = tmp->next_;
      }
    }
  }

  list(list&& l) : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    swap(l);
  }

  ~list() {
    clear();
    delete end_;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() : pointer_(nullptr){};
    ListIterator(Node* pointer) : pointer_(pointer){};

    value_type operator*() {
      if (!pointer_) {
        throw std::invalid_argument("Value is nullptr");
      }
      return pointer_->data_;
    }

    ListIterator operator++(int) {
      pointer_ = pointer_->next_;
      return *this;
    }

    ListIterator& operator++() {
      pointer_ = pointer_->next_;
      return *this;
    }

    ListIterator operator--(int) {
      pointer_ = pointer_->prev_;
      return *this;
    }

    ListIterator& operator--() {
      pointer_ = pointer_->prev_;
      return *this;
    }

    ListIterator& operator+(const value_type step) {
      for (size_type i = 0; i < step; i++) {
        pointer_ = pointer_->next_;
      }
      return *this;
    }

    ListIterator& operator-(const value_type step) {
      for (size_type i = 0; i < step; i++) {
        pointer_ = pointer_->prev_;
      }
      return *this;
    }

    bool operator==(const ListIterator& other) {
      return pointer_ == other.pointer_;
    }
    bool operator!=(const ListIterator& other) {
      return pointer_ != other.pointer_;
    }

   private:
    Node* pointer_;
    friend class list<value_type>;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T& operator*() { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  // ListIterator<T>* li;
  const_reference front() { return head_ ? head_->data_ : end_->data_; }
  const_reference back() { return tail_ ? tail_->data_ : end_->data_; }

  iterator begin() { return head_ ? iterator(head_) : iterator(end_); }
  iterator end() { return iterator(end_); }

  const_iterator begin() const {
    return head_ ? cons_iterator(head_) : const_iterator(end_);
  }
  const_iterator end() const { return const_iterator(end_); }

  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() { return (std::numeric_limits<size_type>::max()); }

  void clear() {
    while (!empty()) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node* tmp = pos.pointer_;
    Node* newnode = new Node(value);

    if (empty()) {
      newnode->next_ = end_;
      newnode->prev_ = end_;
      head_ = newnode;
      tail_ = newnode;
    } else {
      if (tmp == head_) {
        head_ = newnode;
      } else if (tmp == end_) {
        tail_ = newnode;
      }
      newnode->next_ = tmp;
      newnode->prev_ = tmp->prev_;
      tmp->prev_->next_ = newnode;
      tmp->prev_ = newnode;
    }
    size_++;
    ChangeEnd();
    return iterator(newnode);
  }

  void erase(iterator pos) {
    if (empty()) {
      throw std::out_of_range("empty list");
    }
    if (pos.pointer_ == end_) {
      pop_back();
    } else if (pos.pointer_ == head_) {
      pop_front();
    } else {
      pos.pointer_->prev_->next_ = pos.pointer_->next_;
      pos.pointer_->next_->prev_ = pos.pointer_->prev_;
      delete pos.pointer_;
    }
    size_--;
  }

  void push_back(const_reference value) {
    Node* new_node = new Node(value);
    if (empty()) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      new_node->prev_ = tail_;
      tail_->next_ = new_node;
      tail_ = new_node;
    }
    size_++;
    ChangeEnd();
  }

  void pop_back() {
    if (empty()) {
      throw std::out_of_range("empty list");
    }

    Node* tmp = tail_;
    if (size_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      tail_ = tmp->prev_;
      tail_->next_ = tmp->next_;
    }
    delete tmp;
    size_--;
    ChangeEnd();
  }

  void push_front(const_reference value) {
    Node* newnode = new Node(value);
    if (empty()) {
      head_ = newnode;
      tail_ = newnode;
    } else {
      newnode->next_ = head_;
      head_->prev_ = newnode;
      head_ = newnode;
    }
    size_++;
    ChangeEnd();
  }

  void pop_front() {
    if (empty()) {
      throw std::out_of_range("empty list");
    }

    Node* newnode = head_;

    if (size_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = head_->next_;
      head_->prev_ = end_;
    }
    delete newnode;
    size_--;
    ChangeEnd();
  }

  void swap(list& other) {
    Node* tmphead = this->head_;
    Node* tmptail = this->tail_;
    Node* tmpend = this->end_;
    size_type tmpsize = this->size_;

    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->end_ = other.end_;
    this->size_ = other.size_;

    other.head_ = tmphead;
    other.tail_ = tmptail;
    other.end_ = tmpend;
    other.size_ = tmpsize;
  }

  void merge(list& other) {
    iterator this_end = end();

    for (iterator it = other.begin(); it != other.end(); it++) {
      this->insert(this_end, it.pointer_->data_);
      this_end++;
    }
    sort();
  }

  void splice(const_iterator pos, list& other) {
    if (!other.empty()) {
      for (iterator it = other.begin(); it != other.end(); ++it) {
        this->insert(pos, *it);
      }
      other.clear();
    }
  }

  void reverse() {
    if (!this->empty()) {
      size_type step = 0;
      for (iterator it = this->begin(); step <= this->size(); it++) {
        step++;
        std::swap(it.pointer_->prev_, it.pointer_->next_);
      }
      std::swap(head_, tail_);
    }
  }

  void unique() {
    if (empty()) {
      throw std::out_of_range("empty list");
    }

    for (iterator it = begin(); it != end(); it++) {
      if (it.pointer_->data_ == it.pointer_->prev_->data_) {
        erase(it.pointer_->prev_);
      }
    }
  }

  void sort() {
    if (size_ > 1) {
      quicksort(begin(), end()--);
    }
  }

  template <typename... Args>
  void emplace_front(Args&&... args) {
    auto args_list =
        std::initializer_list<value_type>{std::forward<Args>(args)...};

    for (auto& i : args_list) {
      push_front(i);
    }
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    auto args_list =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto& i : args_list) {
      push_back(i);
    }
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    iterator it;
    auto args_list =
        std::initializer_list<value_type>{std::forward<Args>(args)...};

    for (auto& i : args_list) {
      it = insert(pos, i);
    }
    return it;
  }

  iterator partition(iterator start, iterator end) {
    value_type pivot = *end;

    iterator pIndex = start;

    for (iterator i = start; i != end; i++) {
      if (*i <= pivot) {
        std::swap(i.pointer_->data_, pIndex.pointer_->data_);

        pIndex++;
      }
    }
    std::swap(pIndex.pointer_->data_, end.pointer_->data_);

    return pIndex;
  }

  void quicksort(iterator start, iterator end) {
    if (start == end || start == end_ || start == tail_ || end == end_) {
      return;
    }
    iterator pivot = partition(start, end);

    quicksort(start, pivot--);

    quicksort(pivot++, end);
  }
};

}  // namespace s21

#endif  // S21_LIST_H