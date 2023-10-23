#ifndef S21_MAP_H
#define S21_MAP_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename Key, typename T>

class map {
 private:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  struct Node {
    key_type key;
    mapped_type value;
    Node* left_;
    Node* right_;
    Node* up_;

    Node(key_type key = key_type(), mapped_type value = mapped_type())
        : key(key),
          value(value),
          left_(nullptr),
          right_(nullptr),
          up_(nullptr) {}
  };

  Node* head_;
  Node* end_;
  size_type size_;

  void CopySup(const map& other) {
    for (s21::map<key_type, mapped_type>::iterator it = other.begin();
         it != other.end(); ++it) {
      add(it.key, it.value);
    }
  }

  void add(const key_type& key, const mapped_type& data) {
    if (!end_) {
      end_ = AddNewNode(nullptr, end_, key_type(), mapped_type());
      end_->left_ = nullptr;
      end_->right_ = nullptr;
      end_->key = size_--;
      end_->value = size_;
    }

    DelEnd();
    head_ = AddNewNode(nullptr, head_, key, data);
    ChangeEnd();
  }

  Node* AddNewNode(Node* root_up, Node* root, const key_type& key,
                   const mapped_type& data) {
    if (!root) {
      root = new Node(key, data);
      root->up_ = root_up;
      size_++;
    }

    if (key > root->key) {
      root->right_ = AddNewNode(root, root->right_, key, data);
    }

    if (key < root->key) {
      root->left_ = AddNewNode(root, root->left_, key, data);
    }

    return root;
  }

  void DelEnd() {
    if (head_) {
      Node* node_step = head_;
      while (1) {
        if (node_step->right_ == end_) {
          node_step->right_ = nullptr;
          break;
        }

        node_step = node_step->right_;
      }
    }
  }

  void ChangeEnd() {
    Node* node_step = head_;
    while (1) {
      if (node_step->right_ == nullptr) {
        break;
      }

      node_step = node_step->right_;
    }

    end_->up_ = node_step;
    node_step->right_ = end_;

    end_->key = size_;
    end_->value = size_;
  }

 public:
  map() : head_(nullptr), end_(nullptr), size_(0){};
  map(value_type pair) : head_(nullptr), end_(nullptr), size_(0) {
    add(pair.first, pair.second);
  };
  map(std::initializer_list<value_type> const& items)
      : head_(nullptr), end_(nullptr), size_(0) {
    for (const auto& item : items) {
      add(item.first, item.second);
    }
  }

  map(const map& l) : head_(nullptr), end_(nullptr), size_(0) {
    for (s21::map<key_type, mapped_type>::const_iterator it = l.begin();
         it != l.end(); ++it) {
      add(it.operator*().first, it.operator*().second);
    }
  }

  map& operator=(map&& m) {
    swap(m);
    m.clear();
    return *this;
  }

  T& operator=(mapped_type& value) { return value; }

  void swap(map& other) {
    std::swap(head_, other.head_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }

  map(map&& m) : head_(nullptr), end_(nullptr), size_(0) { swap(m); }

  ~map() { clear(); };

  void clear_node(Node* tree) {
    if (tree) {
      clear_node(tree->left_);
      clear_node(tree->right_);
      delete tree;
    }
  }

  void clear() {
    clear_node(head_);
    end_ = nullptr;

    size_ = 0;
  }

  T& at(const Key& key) {
    if (!head_) {
      add(key, mapped_type());
    }

    int flag_in = 0;
    auto it = begin();

    for (; it != end(); ++it) {
      if (key == it.pointer_->key) {
        flag_in = 1;
        break;
      };
    }

    if (flag_in == 0) {
      throw std::out_of_range("No element in map");
    }
    return it.pointer_->value;
  }

  T& operator[](const Key& key) { return at(key); }

  template <typename key_type, typename mapped_type>
  class MapIterator {
   public:
    MapIterator() : pointer_(nullptr){};
    MapIterator(Node* pointer) : pointer_(pointer){};
    ~MapIterator() {}

    std::pair<key_type, mapped_type> operator*() {
      if (pointer_ == find_end()) {
        throw std::out_of_range("Iterator on end");
      }

      if (!pointer_) {
        throw std::invalid_argument("Value is nullptr");
      }

      Node* end_here = find_end();
      if (pointer_ == end_here) {
      }

      return std::make_pair(pointer_->key, pointer_->value);
    }

    MapIterator& operator++() {
      if (!pointer_) {
        std::out_of_range("Empty");
      }

      if (pointer_->right_) {
        pointer_ = pointer_->right_;
        while (pointer_->left_) {
          pointer_ = pointer_->left_;
        }
      } else {
        Node* tmp_ptr = pointer_;
        while (tmp_ptr->up_) {
          tmp_ptr = tmp_ptr->up_;
          if (pointer_->key < tmp_ptr->key) {
            pointer_ = tmp_ptr;
            break;
          }
        }
      }

      return *this;
    }

    MapIterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    MapIterator& operator--() {
      Node* end = find_end();
      if (pointer_ == end) {
        pointer_ = pointer_->up_;
      }

      else if (pointer_->left_) {
        pointer_ = pointer_->left_;
        while (pointer_) {
          pointer_ = pointer_->right_;
        }
      }

      else {
        Node* tmp_ptr = pointer_;
        while (tmp_ptr->up_) {
          tmp_ptr = tmp_ptr->up_;
          if (pointer_->key > tmp_ptr->key) {
            pointer_ = tmp_ptr;
            break;
          }
        }
      }
      return *this;
    }

    MapIterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const MapIterator& other) {
      return pointer_ == other.pointer_;
    }
    bool operator!=(const MapIterator& other) {
      return pointer_ != other.pointer_;
    }

   private:
    Node* find_end() {
      Node* find = pointer_;
      while (find->up_) {
        find = find->up_;
      }
      while (find->right_) {
        find = find->right_;
      }
      return find;
    }

    Node* find_begin() {
      Node* find = pointer_;
      while (find->up_) {
        find = find->up_;
      }
      return find;
    }

    Node* pointer_;
    friend class map<key_type, mapped_type>;
  };

  friend class MapIterator<key_type, mapped_type>;

  template <typename key_type, typename mapped_type>

  class ConstMapIterator : MapIterator<key_type, mapped_type> {
   public:
    ConstMapIterator(MapIterator<key_type, mapped_type> other)
        : MapIterator<key_type, mapped_type>(other) {}

    const std::pair<key_type, mapped_type> operator*() {
      return MapIterator<key_type, mapped_type>::operator*();
    }

    const ConstMapIterator operator++() {
      return MapIterator<key_type, mapped_type>::operator++();
    }
    const ConstMapIterator operator--() {
      return MapIterator<key_type, mapped_type>::operator--();
    }

    bool operator!=(ConstMapIterator<key_type, mapped_type> other) {
      return MapIterator<key_type, mapped_type>::operator!=(other);
    }
  };

  using iterator = MapIterator<key_type, mapped_type>;
  using const_iterator = ConstMapIterator<key_type, mapped_type>;

  iterator begin() {
    if (!head_) {
      throw std::out_of_range("Map Is empty (iterator begin)");
    }

    Node* node_step = head_;
    while (node_step->left_) {
      node_step = node_step->left_;
    }
    return iterator(node_step);
  };

  iterator end() { return iterator(end_); };

  const_iterator begin() const {
    if (!head_) {
      std::out_of_range("Map Is empty (const_iterator begin)");
    }
    Node* node_step = head_;
    while (node_step->left_) {
      node_step = node_step->left_;
    }
    return const_iterator(node_step);
  };

  const_iterator end() const { return const_iterator(end_); };

  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() { return (std::numeric_limits<size_type>::max()); }

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
  return_iterator(const key_type& key) {
    int flag_in = 0;
    std::pair<iterator, bool> return_pair;

    s21::map<key_type, mapped_type>::iterator it = begin();
    for (; it != end(); ++it) {
      if (key == it.pointer_->key) {
        flag_in = 1;
        break;
      };
    }
    if (flag_in) {
      return_pair = std::make_pair(it, true);
    } else {
      return_pair = std::make_pair(it, false);
    }

    return return_pair;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    if (!head_) {
      add(value.first, value.second);
    }
    return insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    if (!head_) {
      add(key, obj);
    }

    std::pair<s21::map<key_type, mapped_type>::iterator, bool> search_pair =
        return_iterator(key);
    std::pair<s21::map<key_type, mapped_type>::iterator, bool> search_it;

    if (!search_pair.second) {
      add(key, obj);
      search_it = std::make_pair(search_pair.first, true);

    } else {
      search_it = std::make_pair(return_iterator(key).first, false);
    }
    return search_it;
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    if (!head_) {
      add(key, obj);
    }

    std::pair<s21::map<key_type, mapped_type>::iterator, bool> search_pair =
        return_iterator(key);

    if (search_pair.second) {
      search_pair.first.pointer_->value = obj;
    }

    else if (!search_pair.second) {
      add(key, obj);
      search_pair = return_iterator(key);
    }
    return search_pair;
  }

  void erase(iterator& pos) {
    if (!pos.pointer_) return;

    if (!pos.pointer_->left_ && !pos.pointer_->right_) {
      pos.pointer_->up_->left_ == pos.pointer_
          ? pos.pointer_->up_->left_ = nullptr
          : pos.pointer_->up_->right_ = nullptr;
      iterator it(pos.pointer_->up_);
      pos = std::move(it);
      return;
    }
    Node* replace = nullptr;
    if (pos.pointer_->left_) {
      replace = pos.pointer_->left_;
      pos.pointer_->left_ = nullptr;
    } else {
      replace = pos.pointer_->right_;
      pos.pointer_->right_ = nullptr;
    }
    if (pos.pointer_ != head_) {
      if (pos.pointer_->up_->left_ == pos.pointer_) {
        pos.pointer_->up_->left_ = replace;
      } else {
        pos.pointer_->up_->right_ = replace;
      }
      std::swap(pos.pointer_->up_, replace->up_);
    } else {
      replace->up_ = replace;
      head_ = replace;
    }
    if (!pos.pointer_->left_ && pos.pointer_->right_) {
      Node* node = replace;
      while (node->right_) {
        node = node->right_;
      }
      node->right_ = pos.pointer_->right_;
      pos.pointer_->right_->up_ = node;
    } else if (pos.pointer_->left_ && !pos.pointer_->right_) {
      Node* node = replace;
      while (node->left_) {
        node = node->left_;
      }
      node->left_ = pos.pointer_->left_;
      pos.pointer_->left_->up_ = node;
    }
    delete pos.pointer_;
    size_--;

    pos = std::move(iterator(replace));
  }

  void merge(map& other) {
    if (other.head_) {
      for (auto it = other.begin(); it != other.end(); it++) {
        if (!return_iterator(it.pointer_->key).second) {
          add(it.pointer_->key, it.pointer_->value);
        };
      }
    }
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args) {
    std::pair<iterator, bool> return_iterator;
    auto args_list =
        std::initializer_list<value_type>{std::forward<Args>(args)...};

    for (auto& i : args_list) {
      return_iterator = insert(i.first, i.second);
    }
    return return_iterator;
  }

  bool contains(const Key& key) {
    std::pair<s21::map<key_type, mapped_type>::iterator, bool> search_pair =
        return_iterator(key);

    bool return_bool = true;
    if (!search_pair.second) {
      return_bool = false;
    }
    return return_bool;
  }
};

}  // namespace s21

#endif  // S21_MAP_H
