template <typename Key, typename Value>
struct Node {
    Key key_;
	
    Value value_;
	
    Node* left_;
	
    Node* right_;
	
    unsigned height_;

    Node(Key key, Value value, Node* left = nullptr, Node* right = nullptr);
};

template <typename Key, typename Value>
class Tree {
public:
    Tree();
	
    Tree(Key key, Value value);
	
    Tree(const Tree& other);
	
    ~Tree();
	
    unsigned size() const;
	
    void insert(const Key& key, const Value& value);
	
    void remove(const Key& key);
	
    Value& operator[](const Key& key);
	
    void clear();

private:
    void deleteNodes(Node<Key, Value>* node);

    Node<Key, Value>* root_;
	
    unsigned size_;
};

template <typename Key, typename Value>
Node<Key, Value>::Node(Key key, Value value, Node* left, Node* right) {
    key_ = key;
    value_ = value;
    left_ = left;
    right_ = right;
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree() {
    root_ = nullptr;
    size_ = 0;
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(Key key, Value value) {
    root_ = new Node<Key, Value>(key, value);
    size_ = 1;
}

template <typename Key, typename Value>
Tree<Key, Value>::~Tree() {
    deleteNodes(root_);
}

template <typename Key, typename Value>
void Tree<Key, Value>::clear() {
    deleteNodes(root_);
    size_ = 0;
}

template <typename Key, typename Value>
void Tree<Key, Value>::deleteNodes(Node<Key, Value>* node) {
    if (node != nullptr) {
        deleteNodes(node->left_);
        deleteNodes(node->right_);
        delete node;
    }
}

template <typename Key, typename Value>
unsigned Tree<Key, Value>::size() const {
    return size_;
}

template <typename Key, typename Value>
void Tree<Key, Value>::insert(const Key& key, const Value& value) {
    if (root_ == nullptr) {
        root_ = new Node<Key, Value>(key, value);
    } else {
        Node<Key, Value>* cur = root_;
        Node<Key, Value>* parent = root_;
        while (cur != nullptr) {
            if (key > cur->key_) {
                cur = cur->right_;
            } else if (key < cur->key_) {
                cur = cur->left_;
            } else {
                cur->value_ = value;
                return;
            }
        }
        cur = new Node<Key, Value>(key, value);
    }
}

template <typename Key, typename Value>
Value& Tree<Key, Value>::operator[](const Key& key) {
    Node<Key, Value>* cur = root_;
    while (cur != nullptr && cur->key_ != key) {
        if (cur->key_ < key) {
            cur = cur->left_;
        } else if (cur->key_ > key) {
            cur = cur->right_;
        } else {
            return cur->value_;
        }
    }
    return root_->value_;
}

template <typename Key, typename Value>
void Tree<Key, Value>::remove(const Key& key) {
    Node<Key, Value>* cur = root_;
}