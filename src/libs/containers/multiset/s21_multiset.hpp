#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <class value_type>
class multiset {
 private:
  using reference = value_type&;
  using const_reference = const value_type&;

  struct Node {
    value_type val_;
    Node* left_{nullptr};
    Node* right_{nullptr};
    Node* parent_{nullptr};

    Node() = default;
    ~Node() = default;
  };

  Node* root_{nullptr};
  Node* end_{nullptr};

 public:
  class iterator {
    friend class multiset;
    Node* current_{nullptr};
    iterator(Node* node) : current_(node){};
    iterator(Node* node, Node* parent, value_type val) {
      current_ = node;
      current_->parent_ = parent;
      current_->val_ = val;
    }

   public:
    iterator() : current_(nullptr){};

    const value_type operator*() { return current_ ? current_->val_ : 0; }

    const value_type* operator->() { return current_ ? &(current_->val_) : 0; }

    bool operator==(const iterator& other) {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) {
      return current_ != other.current_;
    }

    iterator operator++() {
      multiset s;
      current_ = s.next(current_);
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      multiset s;
      current_ = s.next(current_);
      return tmp;
    }

    iterator operator--() {
      multiset s;
      current_ = s.back(current_);
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      multiset s;
      current_ = s.back(current_);
      return tmp;
    }
  };

  class const_iterator {
    friend class multiset;
    const Node* current_{nullptr};
    const_iterator(Node* node) : current_(node){};
    const_iterator(Node* node, Node* parent, value_type val) {
      current_ = node;
      current_->parent_ = parent;
      current_->val_ = val;
    }

   public:
    const_iterator() : current_(nullptr){};

    const value_type operator*() { return current_ ? current_->val_ : 0; }

    const value_type* operator->() { return current_ ? &(current_->val_) : 0; }

    bool operator==(const iterator& other) {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) {
      return current_ != other.current_;
    }

    const_iterator operator++() {
      multiset s;
      current_ = s.next(current_);
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      multiset s;
      current_ = s.next(current_);
      return tmp;
    }

    const_iterator operator--() {
      multiset s;
      current_ = s.back(current_);
      return *this;
    }

    iterator operator--(int) {
      const_iterator tmp = *this;
      multiset s;
      current_ = s.back(current_);
      return tmp;
    }
  };

  multiset() = default;

  multiset(std::initializer_list<value_type> const& items) {
    for (auto& it : items) {
      insert(it);
    }
  }

  multiset(const multiset& s) { copy(s); }

  multiset(multiset&& s) {
    root_ = std::move(s.root_);
    end_ = std::move(s.end_);
    s.root_ = nullptr;
    s.end_ = nullptr;
  }

  ~multiset() { clear(); }

  multiset operator=(multiset& s) {
    copy(s);
    return *this;
  }

  multiset operator=(multiset&& s) {
    root_ = std::move(s.root_);
    end_ = std::move(s.end_);
    s.root_ = nullptr;
    s.end_ = nullptr;
    return *this;
  }

  iterator begin() const {
    if (!root_) return iterator(nullptr);
    Node* node = root_;
    while (node->left_) {
      node = node->left_;
    }
    return iterator(node);
  }

  iterator end() const {
    if (!root_) return iterator(nullptr);
    return iterator(end_);
  }

  bool empty() const { return root_ ? false : true; }

  size_t size() const {
    size_t count = 0;
    for (iterator it = begin(); it != end(); ++it) {
      ++count;
    }
    return count;
  }

  size_t max_size() const {
    return static_cast<size_t>(std::numeric_limits<value_type>::max()) -
           static_cast<size_t>(std::numeric_limits<value_type>::min());
  }

  void clear() {
    if (root_) {
      clearTree(root_);
      root_ = nullptr;
      end_ = nullptr;
    }
  }

  std::pair<multiset<value_type>::iterator, bool> insert(const_reference val) {
    return subunit(root_, val);
  }

  void erase(iterator& pos) {
    if (!pos.current_) return;
    if (!pos.current_->left_ && !pos.current_->right_) {
      pos.current_->parent_->left_ == pos.current_
          ? pos.current_->parent_->left_ = nullptr
          : pos.current_->parent_->right_ = nullptr;
      iterator it(pos.current_->parent_);
      deleteNode(pos.current_);
      pos = std::move(it);
      return;
    }
    Node* replace = nullptr;
    if (pos.current_->left_) {
      replace = pos.current_->left_;
      pos.current_->left_ = nullptr;
    } else {
      replace = pos.current_->right_;
      pos.current_->right_ = nullptr;
    }
    if (pos.current_ != root_) {
      if (pos.current_->parent_->left_ == pos.current_) {
        pos.current_->parent_->left_ = replace;
      } else {
        pos.current_->parent_->right_ = replace;
      }
      std::swap(pos.current_->parent_, replace->parent_);
    } else {
      replace->parent_ = replace;
      root_ = replace;
    }
    if (!pos.current_->left_ && pos.current_->right_) {
      Node* node = replace;
      while (node->right_) {
        node = node->right_;
      }
      node->right_ = pos.current_->right_;
      pos.current_->right_->parent_ = node;
    } else if (pos.current_->left_ && !pos.current_->right_) {
      Node* node = replace;
      while (node->left_) {
        node = node->left_;
      }
      node->left_ = pos.current_->left_;
      pos.current_->left_->parent_ = node;
    }
    deleteNode(pos.current_);
    pos = std::move(iterator(replace));
    --end_->val_;
  }

  void swap(multiset& other) {
    std::swap(root_, other.root_);
    std::swap(end_, other.end_);
  }

  void merge(multiset& other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(it.current_->val_);
    }
  }

  size_t count(const value_type& val) {
    if (!contains(val)) return 0;
    size_t count = 1;
    auto it = find(val);
    auto* node = it.current_;
    while (true) {
      if (node->left_ && node->left_->val_ == val) {
        node = node->left_;
      } else if (node->right_ && node->right_->val_ == val) {
        node = node->right_;
      } else {
        break;
      }
      ++count;
    }
    return count;
  }

  const_iterator find(const_reference val) const {
    return const_search(root_, val).first;
  }

  iterator find(const_reference val) { return search(root_, val).first; }

  bool contains(const_reference val) { return search(root_, val).second; }

  std::pair<iterator, iterator> equal_range(const value_type& val) {
    return std::make_pair(lower_bound(val), upper_bound(val));
  }

  iterator lower_bound(const value_type val) {
    auto res = begin();
    for (; res != end_ && *res < val; res++) {
    }
    return res;
  }

  iterator upper_bound(const value_type val) {
    auto res = begin();
    for (; res != end_ && *res <= val; res++) {
    }
    return res;
  }

  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args) {
    std::pair<iterator, bool> return_iterator = {nullptr, false};
    auto args_list =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto& i : args_list) {
      return_iterator = insert(i);
    }
    return return_iterator;
  }

 protected:
  std::pair<multiset<value_type>::iterator, bool> addVal(Node*& node,
                                                         Node*& parent,
                                                         const value_type val) {
    std::pair<multiset<value_type>::iterator, bool> res = {nullptr, false};
    node = new Node;
    res = {iterator(node, parent, val), true};
    if (end_) ++end_->val_;
    return res;
  }

  std::pair<multiset<value_type>::iterator, bool> makeEnd(const_reference val) {
    std::pair<multiset<value_type>::iterator, bool> res = {nullptr, false};
    Node* node = new Node;
    node->val_ = val;
    end_->parent_->right_ = node;
    node->right_ = end_;
    node->parent_ = std::move(end_->parent_);
    end_->parent_ = node;
    ++end_->val_;
    return res = {node, true};
  }

  std::pair<multiset<value_type>::iterator, bool> subunit(
      Node*& node, const value_type val) {
    std::pair<multiset<value_type>::iterator, bool> res = {nullptr, false};
    if (!node) {
      res = addVal(node, node, val);
      end_ = addVal(node->right_, node, 1).first.current_;
    } else if (val < node->val_) {
      res = node->left_ ? subunit(node->left_, val)
                        : addVal(node->left_, node, val);
    } else if (val > node->val_) {
      res = node->right_   ? subunit(node->right_, val)
            : node == end_ ? makeEnd(val)
                           : addVal(node->right_, node, val);
    } else if (val == node->val_) {
      res = insertDuplicate(node, val);
      // std::cout << "DUPLICATE: " << val << std::endl;
    }
    return res;
  }

  //       9
  //     1   17
  //   1
  // -3
  std::pair<multiset<value_type>::iterator, bool> insertDuplicate(
      Node*& node, const value_type val) {
    std::pair<multiset<value_type>::iterator, bool> res = {nullptr, false};
    Node* duplicate{nullptr};
    res = addVal(duplicate, node, val);
    if (node->left_) {
      std::swap(node->left_, duplicate->left_);
      node->left_ = duplicate;
      duplicate->left_->parent_ = duplicate;
    } else if (node->right_) {
      std::swap(node->right_, duplicate->right_);
      node->right_ = duplicate;
      duplicate->right_->parent_ = duplicate;
    } else {
      node->right_ = duplicate;
      duplicate->parent_ = node;
    }
    return res;
  }

  std::pair<multiset<value_type>::const_iterator, bool> const_search(
      const Node* node, const_reference val) const {
    std::pair<const multiset<value_type>::const_iterator, bool> res;
    if (!node) {
      return res;
    } else if (val < node->val_) {
      return const_search(node->left_, val);
    } else if (val > node->val_) {
      return const_search(node->right_, val);
    } else if (val == node->val_) {
      const_iterator it;
      it.current_ = node;
      return {it, true};
    }
    return res;
  }

  std::pair<multiset<value_type>::iterator, bool> search(
      Node*& node, const_reference val) const {
    std::pair<multiset<value_type>::iterator, bool> res = {nullptr, false};
    Node* seek = node;
    while (seek) {
      if (val < seek->val_) {
        seek = seek->left_;
      } else if (val > seek->val_) {
        seek = seek->right_;
      } else if (val == seek->val_) {
        res = {seek, true};
        break;
      }
    }
    return res;
  }

  void copy(const multiset& s) {
    insert(s.root_->val_);
    for (iterator it = s.begin(); it != s.end(); ++it) {
      if (*it == s.root_->val_) continue;
      insert(it.current_->val_);
    }
  }

  void deleteNode(Node*& node) {
    node->val_ = 0;
    node->left_ = nullptr;
    node->right_ = nullptr;
    node->parent_ = nullptr;
    delete node;
  }

  void clearTree(Node*& tree) {
    if (tree) {
      clearTree(tree->left_);
      clearTree(tree->right_);
      delete tree;
    }
  }

  Node* next(Node*& current) const {
    if (!current) {
      return nullptr;
    }
    Node* run = current;
    if (current->right_) {
      run = current->right_;
      while (run->left_) {
        run = run->left_ ? run->left_ : run->right_;
      }
    } else if (!current->right_) {
      Node* curr = run;
      run = run->parent_;
      while (run->val_ <= curr->val_) {
        run = run->parent_;
      }
    }
    return run;
  }

  Node* back(Node*& current) const {
    if (!current) {
      return nullptr;
    }
    Node* run = current;
    if (current->left_) {
      run = current->left_;
      while (run->right_) {
        run = run->right_;
      }
    } else if (!current->left_) {
      Node* curr = run;
      run = run->parent_;
      while (run->val_ >= curr->val_) {
        run = run->parent_;
      }
    }
    return run;
  }
};
}  // namespace s21
