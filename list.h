template <typename T>
struct Node {
    T value_;
    Node* prev_;
    Node* next_;

    Node() {
        value_ = T();
        prev_ = next_ = nullptr;
    }

    Node(const T& value, Node* next_, Node* prev) {
        value_ = T(value);
        next_ = next_;
        prev_ = prev;
    }
};

template <typename T>
class List {
private:
    Node<T>* first_, * last_;
    unsigned size_;

public:
    List();
    List(const List& other);
    ~List();
    unsigned size() const;
    void append(const T& obj);
    void insert(unsigned index, const T& obj);
    void remove(unsigned index);
    void clear();
    T& at(unsigned index) const;
    T& first() const;
    T& last() const;

    class Iterator {
    private:
        Node<T>* ptr;

    public:
        Iterator(Node<T>* temp) : ptr(temp) {}
        Iterator(const Iterator& it2) : ptr(it2.ptr) {}
        T& operator*();
        const T& operator*() const;
        Iterator& operator+(const int n);
        Iterator& operator++(int);
        Iterator operator++();
        Iterator& operator-(const int n);
        Iterator& operator--(int);
        Iterator operator--();
        bool operator==(const Iterator& i) const;
        bool operator != (const Iterator& i) const;
    };

    Iterator begin() const;
    Iterator end() const;
    List& operator=(const List& other);
    bool operator==(const List& other);
    bool operator!=(const List& other);
};

template <typename T>
List<T>::List() {
    last_ = first_ = nullptr;
    size_ = 0;
}

template <typename T>
List<T>::List(const List<T>& other) {
    size_ = 0;
    last_ = first_ = nullptr;
    for (Iterator it = other.begin(); it != other.end(); ++it) {
        append(*it);
    }
}

template <typename T>
List<T>::~List() {
    while (first_ != nullptr) {
        Node<T>* temp = first_->next_;
        delete first_;
        first_ = temp;
    }
}

template <typename T>
unsigned List<T>::size() const {
    return size_;
}

template <typename T>
void List<T>::append(const T& obj) {
    if (first_ == nullptr) {
        first_ = new Node<T>(obj, last_, nullptr);
        last_ = first_;
    } else {
        last_->next_ = new Node<T>(obj, nullptr, last_);
        last_ = last_->next_;
    }
    size_++;
}

template <typename T>
void List<T>::insert(unsigned index, const T& obj) {
    if (first_ == nullptr) {
        append(obj);
    } else {
        Node<T>* cur = first_;
        for (unsigned i = 0; i < index; ++i) {
            cur = cur->next_;
        }
        if (cur->next_) {
            Node<T>* new_node = new Node<T>(obj, cur->next_, cur);
            cur->next_->prev_ = new_node;
            cur->next_ = new_node;
        } else {
            append(obj);
        }
    }
}

template <typename T>
void List<T>::remove(unsigned index) {
    unsigned i = 0;
    Node<T>* temp = first_;
    while (i < index) {
        temp = temp->next_;
        ++i;
    }
    if (temp == first_) {
        if (size_ == 1) {
            delete first_;
            first_ = nullptr;
            size_ = 0;
        } else {
            first_->next_->prev_ = nullptr;
            first_ = first_->next_;
            delete temp;
            size_--;
        }
    } else {
        temp->prev_->next_ = temp->next_;
        temp->next_->prev_ = temp->prev_;
        delete temp;
        size_--;
    }
}

template <typename T>
void List<T>::clear() {
    while (first_ != nullptr) {
        Node<T>* temp = first_->next_;
        delete first_;
        first_ = temp;
    }
    size_ = 0;
}

template <typename T>
T& List<T>::Iterator::operator*() {
    return ptr->value_;
}

template <typename T>
const T& List<T>::Iterator::operator*() const {
    return ptr->value_;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator+(const int n) {
    for (int i = 0; i < n; i++) {
        ptr = ptr->next_;
    }
    return *this;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++(int) {
    ptr = ptr->next_;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++() {
    Iterator iterator(ptr);
    ptr = ptr->next_;
    return iterator;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator-(const int n) {
    for (int i = 0; i < n; i++) {
        ptr = ptr->prev_;
    }
    return *this;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--(int) {
    ptr = ptr->prev_;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--() {
    Iterator iterator(ptr);
    ptr = ptr->prev_;
    return iterator;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& i) const {
    return i.ptr == this->ptr;
}

template <typename T>
bool List<T>::Iterator::operator != (const Iterator& i) const {
    return i.ptr != this->ptr;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(first_);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(last_->next_);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    clear();
    for (Iterator it = other.begin(); it != other.end(); ++it) {
        append(*it);
    }
    return *this;
}

template <typename T>
bool List<T>::operator==(const List<T>& other) {
    if (size_ != other.size_)
        return false;
    for (Iterator it1 = begin(), it2 = other.begin(); it1 != end(); ++it1, ++it2)
        if (*it1 != *it2)
            return false;
    return true;
}

template <typename T>
bool List<T>::operator!=(const List<T>& other) {
    return !(*this == other);
}

template <typename T>
T& List<T>::at(unsigned index) const {
    auto it = begin();
    for (int i = 0; i < index; ++i, ++it);
    return *it;
}

template <typename T>
T& List<T>::first() const {
    return first_->value_;
}

template <typename T>
T& List<T>::last() const {
    return last_->value_;
}
