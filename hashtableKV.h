#include <functional>
const double DEFAULT_COEF_FULL = 0.5;

template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node(KeyType, ValueType);
};

template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable();
    HashTable(const HashTable& other);
    ~HashTable();

    void insert(KeyType key, ValueType value);
    ValueType& operator[](KeyType key);
    ValueType find(KeyType key);
    void remove(KeyType key);
    unsigned size() const;
    unsigned capacity() const;
    void clear();    

private:
    unsigned size_;
    unsigned capacity_;
    double coef_full_;
    Node<KeyType, ValueType>** items_;
    unsigned index(KeyType key);
    void rehash();
    Func hasher_{ Func() };
};

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::Node(KeyType key, ValueType value) {
    key_ = key;
    value_ = value;
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable() {
    capacity_ = 100;
    size_ = 0;
    coef_full_ = DEFAULT_COEF_FULL;
    items_ = new Node<KeyType, ValueType>*[capacity_];
	
    for (unsigned i = 0; i < capacity_; ++i) {
        items_[i] = nullptr;
    }
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable(const HashTable& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    coef_full_ = other.coef_full_;
    items_ = new Node<KeyType, ValueType>*[capacity_];
	
    for (unsigned i = 0; i < capacity_; ++i) {
        if (other.items_[i] == nullptr) {
            items_[i] = nullptr;
        } else {
            items_[i] = new Node(other.items_[i]->key_, other.items_[i]->value_);
        }
    }
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::~HashTable() {
    if (items_) {
        for (unsigned i = 0; i < capacity_; ++i) {
            if (items_[i] != nullptr) {
                delete items_[i];
            }
        }
		
        delete[] items_;
    }
}

template <class KeyType, class ValueType, class Func>
unsigned HashTable<KeyType, ValueType, Func>::index(KeyType key) {
    return hasher_(key) % capacity_;
}

template <class KeyType, class ValueType, class Func>
unsigned HashTable<KeyType, ValueType, Func>::size() const {
    return size_;
}

template <class KeyType, class ValueType, class Func>
unsigned HashTable<KeyType, ValueType, Func>::capacity() const {
    return capacity_;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::insert(KeyType key, ValueType value) {
    unsigned ind = index(key);
    while (items_[ind] != nullptr && items_[ind]->key_ != key) {
        ind++;
    }
	
    if (items_[ind] == nullptr) {
        items_[ind] = new Node<KeyType, ValueType>(key, value);
        size_++;
    } else if (items_[ind] != nullptr && items_[ind]->key_ == key) {
        items_[ind]->value_ = value;
    }
	
    if (size_ > capacity_ * coef_full_) {
        rehash();
    }
}

template <class KeyType, class ValueType, class Func>
ValueType HashTable<KeyType, ValueType, Func>::find(KeyType key) {
    unsigned ind = index(key);
    if (items_[ind]) {
        while (items_[ind] != nullptr && items_[ind]->key_ != key) {
            ind++;
        }
		
        if (items_[ind] == nullptr) {
            throw;
        } else {
            return items_[ind]->value_;
        }
    }
    throw;
}

template <class KeyType, class ValueType, class Func>
ValueType& HashTable<KeyType, ValueType, Func>::operator[](KeyType key) {
    unsigned ind = index(key);
    if (items_[ind]) {
        while (items_[ind] != nullptr && items_[ind]->key_ != key) {
            ind++;
        }
        if (items_[ind] == nullptr) {
            throw;
        } else {
            return items_[ind]->value_;
        }
    }
    throw;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::clear() {
    if (items_) {
        for (unsigned i = 0; i < capacity_; ++i) {
            if (items_[i]) {
                delete items_[i];
            }
        }
		
        delete[] items_;
    }
    items_ = new Node<KeyType, ValueType> * [capacity_];
	
    for (unsigned i = 0; i < capacity_; ++i) {
        items_[i] = nullptr;
    }
    size_ = 0;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::remove(KeyType key) {
    unsigned ind = index(key);
	
    if (items_[ind]) {
        while (items_[ind] != nullptr && items_[ind]->key_ != key) {
            ind++;
        }
		
        if (items_[ind]) {
            delete items_[ind];
            items_[ind] = nullptr;
            size_--;
        }
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::rehash() {
    unsigned new_capacity = capacity_ * 2;
    Node<KeyType, ValueType>** new_items = new Node<KeyType, ValueType> * [new_capacity];
	
    for (unsigned i = 0; i < new_capacity; ++i) {
        new_items[i] = nullptr;
    }
	
    for (unsigned i = 0; i < capacity_; ++i) {
        if (items_[i] != nullptr) {
            unsigned index = hasher_(items_[i]->key_) % new_capacity;
            while (new_items[index] != nullptr) {
                ++index;
            }
            new_items[index] = new Node<KeyType, ValueType>(items_[i]->key_, items_[i]->value_);
        }
    }
	
    for (unsigned i = 0; i < capacity_; ++i) {
        delete items_[i];
    }
	
    delete[] items_;
    items_ = new_items;
    capacity_ = new_capacity;
}
