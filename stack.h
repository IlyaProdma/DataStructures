template <typename T>
struct StackItem {
		StackItem *prev_, *next_;
		T value_;

		StackItem() {
			value_ = T();
			next_ = nullptr;
		}
		StackItem(const T& t, StackItem* nt) {
			value_ = T(t);
			next_ = nt;
		}
		StackItem(const T& t) {
			value_ = T(t);
			next_ = nullptr;
		}
};

template <typename T>
class Stack {
public:
	Stack();
	Stack(T value_);
	Stack(const Stack& stack);
	~Stack();
	unsigned size() const;
	void push(const T& value_);
	T pop();
	T& top() const;
	void clear();
	void changeTop(const T& new_value);

	class Iterator {
	public:
		Iterator(StackItem<T>* temp) : ptr(temp) {}
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
		StackItem<T>* ptr;
	};

	Iterator begin() const;
	Iterator end() const;
	Stack& operator=(const Stack& stack);
	bool operator==(const Stack& other) const;
	bool operator!=(const Stack& other) const;

private:
	unsigned size_;
	StackItem<T>* top_;
	StackItem<T>* first_;
};

template <typename T>
Stack<T>::Stack()  {
		size_ = 0;
		first_ = nullptr;
		top_ = first_;
}

template <typename T>
Stack<T>::Stack(T value_) {
	size_ = 1;
	first_ = new StackItem<T>(value_);
	top_ = first_;
}

template <typename T>
Stack<T>::Stack(const Stack& stack) {
	Stack::Iterator it = stack.begin();
	for (it; it != stack.end(); ++it) {
		push(*it);
	}
}

template <typename T>
Stack<T>::~Stack() {
	while (top_ != nullptr)
	{
		StackItem<T>* temp;
		temp = top_->next_;
		delete top_;
		top_ = temp;
	}
}

template <typename T>
unsigned Stack<T>::size() const {
	return size_;
}

template <typename T>
void Stack<T>::push(const T& value) {
	size_++;
	if (top_ == nullptr) {
		first_ = new StackItem<T>(value, nullptr);
		top_ = first_;
	}
	else {
		StackItem<T>* temp = top_;
		top_ = new StackItem<T>(value, temp);
		temp->prev_ = top_;
	}
}

template <typename T>
T Stack<T>::pop() {
	size_--;
	T result = top_->value_;
	StackItem<T>* to_delete = top_;
	top_ = top_->next_;
	top_->prev = nullptr;
	delete to_delete;
	return result;
}

template <typename T>
T& Stack<T>::top() const {
	return top_->value_;
}

template <typename T>
void Stack<T>::clear() {
	while (top_ != nullptr)
	{
		StackItem<T>* temp;
		temp = top_->next_;
		delete top_;
		top_ = temp;
	}
	size_ = 0;
}

template <typename T>
void Stack<T>::changeTop(const T& new_value) {
	this->top_->value_ = new_value;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const {
	return Iterator(first_);
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const {
	return Iterator(top_->prev_);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& stack) {
	clear();
	Stack::Iterator it = stack.begin();
	for (it; it != stack.end(); ++it) {
		push(*it);
	}
	return *this;
}

template <typename T>
bool Stack<T>::operator==(const Stack& other) const {
	if (this->size() != other.size())
		return false;
	for (Iterator it1 = begin(), it2 = other.begin(); it1 != end(); ++it1, ++it2)
		if (*it1 != *it2)
			return false;
	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& other) const {
	return !(*this == other);
}

template <typename T>
T& Stack<T>::Iterator::operator*() {
			return ptr->value_;
}

template <typename T>
const T& Stack<T>::Iterator::operator*() const {
	return ptr->value_;
}

template <typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator+(const int n) {
	for (int i = 0; i < n; i++)
		ptr = ptr->prev_;
	return *this;
}

template <typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator-(const int n) {
	for (int i = 0; i < n; i++)
		ptr = ptr->next_;
	return *this;
}

template <typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator++(int) {
	ptr = ptr->prev_;
	return *this;
}

template <typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator--(int) {
	ptr = ptr->next_;
	return *this;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::Iterator::operator++() {
	Iterator iterator(ptr);
	ptr = ptr->prev_;
	return iterator;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::Iterator::operator--() {
	Iterator iterator(ptr);
	ptr = ptr->next_;
	return iterator;
}

template <typename T>
bool Stack<T>::Iterator::operator==(const Iterator& i) const {
	return i.ptr == this->ptr;
}

template <typename T>
bool Stack<T>::Iterator::operator!=(const Iterator& i) const {
	return i.ptr != this->ptr;
}
