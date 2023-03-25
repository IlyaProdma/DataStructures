template <typename T>
class Matrix {
private:
    T** data_;
    unsigned size_rows_;
    unsigned size_columns_;

public:
    Matrix(unsigned size_rows, unsigned size_columns);
    Matrix(const Matrix& other);
    ~Matrix();
    unsigned count() const;
    unsigned rows() const;
    unsigned columns() const;
    T& at(unsigned row, unsigned column);
    T* operator[](unsigned row);
    Matrix& operator=(const Matrix& other);  
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

template <typename T>
Matrix<T>::Matrix(unsigned size_rows, unsigned size_columns) {
    this->size_rows_ = size_rows;
    this->size_columns_ = size_columns;
    data_ = new T*[size_rows_];
    for (unsigned i = 0; i < size_rows_; ++i) {
        data_[i] = new T[size_columns_];
        for (unsigned j = 0; j < size_columns_; ++j) {
            data_[i][j] = T();
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) {
    this->size_rows_ = other.size_rows_;
    this->size_columns_ = other.size_columns_;
    data_ = new T*[size_rows_];
    for (unsigned i = 0; i < size_rows_; ++i) {
        data_[i] = new T[size_columns_];
        for (unsigned j = 0; j < size_columns_; ++j) {
            data_[i][j] = T(other.data_[i][j]);
        }
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    for (unsigned i = 0; i < size_rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}

template <typename T>
unsigned Matrix<T>::count() const {
    return size_rows_*size_columns_;
}

template <typename T>
unsigned Matrix<T>::rows() const {
    return size_rows_;
}

template <typename T>
unsigned Matrix<T>::columns() const {
    return size_columns_;
}

template <typename T>
T* Matrix<T>::operator[](unsigned row) {
    return data_[row];
}

template <typename T>
T& Matrix<T>::at(unsigned row, unsigned column) {
    return data_[row][column];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    for (unsigned i = 0; i < size_rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;    
    size_rows_ = other.size_rows_;
    size_columns_ = other.size_columns_;
    data_ = new T*[size_rows_];
    for (unsigned i = 0; i < size_rows_; ++i) {
        data_[i] = new T[size_columns_];
        for (unsigned j = 0; j < size_columns_; ++j) {
            data_[i][j] = other.data_[i][j];
        }
    }
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (size_rows_ != other.size_rows_ || size_columns_ != other.size_columns_) {
        return false;
    }
    for (unsigned i = 0; i < size_rows_; ++i) {
        for (unsigned j = 0; j < size_columns_; ++j) {
            if (data_[i][j] != other.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
    return !(*this == other);
}
