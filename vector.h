#include <cmath>
const int DEFAULT_SIZE = 20;
const double COEF_FULL = 0.8;
const double COEF_RESIZE = 1.25;

template <typename T>
class Vector {
private:
    T* data_;
    unsigned size_;
    unsigned capacity_;

public:
    Vector();
    Vector(unsigned capacity);
    Vector(const Vector& other);
    ~Vector();
    unsigned size() const;
    unsigned capacity() const;
    void clear();
    void append(const T& item);
    void insert(unsigned index, const T& item);
    bool empty() const;
    void remove(unsigned index);
    void resize(unsigned new_capacity);
    void shrinkToFit(unsigned new_capacity);
    T& operator[](unsigned index);
    T at(unsigned index);
    Vector& operator=(const Vector& other);    
    bool operator==(const Vector& other);
    bool operator!=(const Vector& other);
};

template <typename T>
Vector<T>::Vector() {
    data_ = new T[DEFAULT_SIZE];
    size_ = 0;
    capacity_ = DEFAULT_SIZE;
    for (int i = 0; i < capacity_; ++i) {
        data_[i] = T();
    }
}

template <typename T>
Vector<T>::Vector(unsigned capacity) {
    size_ = 0;
    capacity_ = capacity;
    data_ = new T[capacity];
    for (int i = 0; i < capacity_; ++i) {
        data_[i] = T();
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];
    for (int i = 0; i < other.size_; ++i) {
        data_[i] = T(other.data_[i]);
    }
    for (int i = other.size_; i < other.capacity_; ++i) {
        data_[i] = T();
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <typename T>
void Vector<T>::clear() {
    delete[] data_;
    data_ = new T[capacity_];
    size_ = 0;
}

template <typename T>
unsigned Vector<T>::size() const {
    return size_;
}

template <typename T>
unsigned Vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
void Vector<T>::append(const T& item) {
    data_[size_] = item;
    size_++;
    if (size_ > capacity_ * COEF_FULL) {
        resize(std::round(size_*COEF_RESIZE));
    }
}

template <typename T>
void Vector<T>::resize(unsigned new_capacity) {
    if (new_capacity > capacity_) {
        T* temp_data = new T[new_capacity];
        for (int i = 0; i < capacity_; ++i) {
            temp_data[i] = data_[i];
        }
        for (int i = capacity_; i < new_capacity; ++i) {
            temp_data[i] = T();
        }
        delete[] data_;
        data_ = temp_data;
        capacity_ = new_capacity;
    } else if (new_capacity < size_) {
        size_ = new_capacity;
    }
}

template <typename T>
void Vector<T>::shrinkToFit(unsigned new_capacity) {
    if (new_capacity > capacity_) {
        resize(new_capacity);
    } else if (new_capacity < size_) {
        size_ = new_capacity;
        T* temp_data = new T[new_capacity+1];
        for (int i = 0; i < new_capacity; ++i) {
            temp_data[i] = data_[i];
        }
        capacity_ = new_capacity+1;
        temp_data[new_capacity] = T();
        delete data_;
        data_ = temp_data;
    }
}

template <typename T>
void Vector<T>::insert(unsigned index, const T& item) {
    if (index >= size_) {
        append(item);
    } else {
        for (unsigned i = size_; i > index; --i) {
            data_[i] = data_[i-1];
        }
        data_[index] = item;
        size_++;
    }
}

template <typename T>
void Vector<T>::remove(unsigned index) {
    for (int i = index; i < size_; ++i) {
        data_[i] = data_[i+1];
    }
    size_--;
}

template <typename T>
bool Vector<T>::empty() const {
    return size_ <= 0;
}

template <typename T>
T& Vector<T>::operator[](unsigned index) {
    return data_[index];
}

template <typename T>
T Vector<T>::at(unsigned index) {
    return data_[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];
    for (unsigned i = 0; i < other.size_; ++i) {
        data_[i] = T(other.data_[i]);
    }
    for (unsigned i = other.size_; i < other.capacity_; ++i) {
        data_[i] = T();
    }
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) {
    if (size_ != other.size_) {
        return false;
    }
    for (unsigned i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& other) {
    return !(*this == other);
}
