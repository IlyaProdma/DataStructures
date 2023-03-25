#include <functional>

template <typename T>
struct Node {
    T value_;
    Node(T value);
};

template <class T, class Func = std::hash<T>>
class HashTable {
public:
    HashTable();
    HashTable(const HashTable& other);
    ~HashTable();

    void insert(const T& value);
    bool operator[](const T& value);
    bool find(const T& value);
    void remove(const T& value);
    unsigned size() const;
    unsigned capacity() const;
    void clear();

private:
    unsigned size_;
    unsigned capacity_;
    double coef_full_;
    Node<T>** items_;
    unsigned index(const T& value);
    void rehash();
    Func hasher_{ Func() };
};

template <class T>
Node<T>::Node(T value) {
    value_ = value;
}

template <class T, class Func>
HashTable<T, Func>::HashTable() {
    capacity_ = 100;
    size_ = 0;
    coef_full_ = 0.5;
    items_ = new Node<T> * [capacity_];
    for (unsigned i = 0; i < capacity_; ++i) {
        items_[i] = nullptr;
    }
}

template <class T, class Func>
HashTable<T, Func>::HashTable(const HashTable& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    coef_full_ = other.coef_full_;
    items_ = new Node<T>*[capacity_];
    for (unsigned i = 0; i < capacity_; ++i) {
        if (other.items_[i] == nullptr) {
            items_[i] = nullptr;
        } else {
            items_[i] = new Node(other.items_[i]->value_);
        }
    }
}

template <class T, class Func>
HashTable<T, Func>::~HashTable() {
    if (items_) {
        for (unsigned i = 0; i < capacity_; ++i) {
            if (items_[i] != nullptr) {
                delete items_[i];
            }
        }
        delete[] items_;
    }
}

template <class T, class Func>
unsigned HashTable<T, Func>::index(const T& value) {
    return hasher_(value) % capacity_;
}

template <class T, class Func>
unsigned HashTable<T, Func>::size() const {
    return size_;
}

template <class T, class Func>
unsigned HashTable<T, Func>::capacity() const {
    return capacity_;
}

template <class T, class Func>
void HashTable<T, Func>::insert(const T& value) {
    unsigned ind = index(value);
    while (items_[ind] != nullptr) {
        if (items_[ind]->value_ == value) {
            return;
        }
        ind++;
    }
    if (items_[ind] == nullptr) {
        items_[ind] = new Node<T>(value);
        size_++;
    }
    if (size_ > capacity_ * coef_full_) {
        rehash();
    }
}

template <class T, class Func>
bool HashTable<T, Func>::find(const T& value) {
    unsigned ind = index(value);
    if (items_[ind]) {
        while (items_[ind] != nullptr && items_[ind]->value_ != value) {
            ind++;
        }
        return (items_[ind] != nullptr);
    }
    throw;
}

template <class T, class Func>
bool HashTable<T, Func>::operator[](const T& value) {
    unsigned ind = index(value);
    if (items_[ind]) {
        while (items_[ind] != nullptr && items_[ind]->value_ != value) {
            ind++;
        }
        return (items_[ind] != nullptr);
    }
    throw;
}

template <class T, class Func>
void HashTable<T, Func>::clear() {
    if (items_) {
        for (unsigned i = 0; i < capacity_; ++i) {
            if (items_[i]) {
                delete items_[i];
            }
        }
        delete[] items_;
    }
    items_ = new Node<T>*[capacity_];
    for (unsigned i = 0; i < capacity_; ++i) {
        items_[i] = nullptr;
    }
    size_ = 0;
}

template <class T, class Func>
void HashTable<T, Func>::remove(const T& value) {
    unsigned ind = index(value);
    if (items_[ind]) {
        while (items_[ind] != nullptr && items_[ind]->value_ != value) {
            ind++;
        }
        if (items_[ind]) {
            delete items_[ind];
            items_[ind] = nullptr;
            size_--;
        }
    }
}

template <class T, class Func>
void HashTable<T, Func>::rehash() {
    unsigned new_capacity = capacity_ * 2;
    Node<T>** new_items = new Node<T> * [new_capacity];
    for (unsigned i = 0; i < new_capacity; ++i) {
        new_items[i] = nullptr;
    }
    for (unsigned i = 0; i < capacity_; ++i) {
        if (items_[i] != nullptr) {
            unsigned index = hasher_(items_[i]->value_) % new_capacity;
            while (new_items[index] != nullptr) {
                ++index;
            }
            new_items[index] = new Node<T>(items_[i]->value_);
        }
    }
    for (unsigned i = 0; i < capacity_; ++i) {
        delete items_[i];
    }
    delete[] items_;
    items_ = new_items;
    capacity_ = new_capacity;
}
