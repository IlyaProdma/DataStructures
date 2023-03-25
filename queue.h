template <typename T>
struct Node {
    T value_;
    Node* next_;
    Node* prev_;

    Node() {
        next_ = nullptr;
        value_ = T();
    }

    Node(const T& t, Node* nt){
        value_ = T(t);
		next_ = nt;
    }

    Node(const T& t) {
        value_ = T(t);
        next_ = nullptr;
    }
};

template <typename T>
class Queue {
public:
    Queue();
    Queue(const T& value);
    Queue(const Queue& other);
    ~Queue();
    unsigned size() const;
    void push_back(const T& value);
    T pop_front();
    T& front() const;
    void clear();

    class Iterator {
	public:
		Iterator(Node<T>* temp) : ptr(temp) {}
		Iterator(const Iterator& it2) : ptr(it2.ptr) {}
		T& operator*();
		const T& operator*() const;
		Iterator& operator+(const int n);
		Iterator& operator- (const int n);
		Iterator& operator++(int);
		Iterator& operator--(int);
		Iterator operator++();
		Iterator operator--();
		bool operator==(const Iterator& i) const;
		bool operator!=(const Iterator& i) const;


	private:
		Node<T>* ptr;
	};

    Iterator begin() const;
	Iterator end() const;
	Queue& operator=(const Queue& stack);
	bool operator==(const Queue& other) const;
	bool operator!=(const Queue& other) const;

private:
	unsigned size_;
	Node<T>* back_;
	Node<T>* front_;

};

template <typename T>
Queue<T>::Queue() {
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
}

template <typename T>
Queue<T>::Queue(const T& value) {
    size_ = 1;
    front_ = new Node<T>(value);
    back_ = front_;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
    Queue::Iterator it = other.begin();
    for (it; it != other.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
Queue<T>::~Queue() {
    while (front_ != nullptr) {
        Node<T>* to_delete = front_;
        front_ = front_->next_;
        delete to_delete;
    }
}

template <typename T>
unsigned Queue<T>::size() const {
    return size_;
}

template <typename T>
void Queue<T>::push_back(const T& value) {
    if (size_ > 0) {
        back_->next_ = new Node<T>(value, nullptr);
        back_ = back_->next_;
    } else {
        back_ = front_ = new Node<T>(value, nullptr);
    }
    size_++;
}

template <typename T>
T Queue<T>::pop_front() {
    if (front_ != nullptr) {
        T result = front_->value_;
        Node<T>* temp = front_->next_;
        delete front_;
        front_ = temp;
        size_--;
        return result;
    } else {
        throw;
    }
}

template <typename T>
T& Queue<T>::front() const {
    return front_->value_;
}

template <typename T>
void Queue<T>::clear() {
    while (front_ != nullptr) {
        Node<T>* to_delete = front_;
        front_ = front_->next_;
        delete to_delete;
    }
    size_ = 0;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const {
	return Iterator(front_);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const {
	return Iterator(nullptr);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& queue) {
	clear();
	Queue::Iterator it = queue.begin();
	for (it; it != queue.end(); ++it) {
		push_back(*it);
	}
	return *this;
}

template <typename T>
bool Queue<T>::operator==(const Queue& other) const {
	if (this->size() != other.size())
		return false;
	for (Iterator it1 = begin(), it2 = other.begin(); it1 != end(); ++it1, ++it2)
		if (*it1 != *it2)
			return false;
	return true;
}

template <typename T>
bool Queue<T>::operator!=(const Queue& other) const {
	return !(*this == other);
}

template <typename T>
T& Queue<T>::Iterator::operator*() {
	return ptr->value_;
}

template <typename T>
const T& Queue<T>::Iterator::operator*() const {
	return ptr->value_;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator+(const int n) {
	for (int i = 0; i < n; i++)
		ptr = ptr->next_;
	return *this;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator-(const int n) {
	for (int i = 0; i < n; i++)
		ptr = ptr->prev_;
	return *this;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(int) {
	ptr = ptr->next_;
	return *this;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator--(int) {
	ptr = ptr->prev_;
	return *this;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++() {
	Iterator iterator(ptr);
	ptr = ptr->next_;
	return iterator;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator--() {
	Iterator iterator(ptr);
	ptr = ptr->prev_;
	return iterator;
}

template <typename T>
bool Queue<T>::Iterator::operator==(const Iterator& i) const {
	return i.ptr == this->ptr;
}

template <typename T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const {
	return i.ptr != this->ptr;
}
