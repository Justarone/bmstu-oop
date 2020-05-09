template <typename T>
void ConstIterator<T>::_index_check(const string hint) const {
    if (_index < _rows * _cols)
        return;
    time_t cur_time = time(NULL);
    auto local_time = localtime(&cur_time);
    throw IndexError(asctime(local_time), __FILE__, __LINE__, hint);
}

template <typename T>
bool ConstIterator<T>::operator!=(ConstIterator const& other) const {
    return _index != other._index;
}

template <typename T>
bool ConstIterator<T>::operator==(ConstIterator const& other) const {
    return _index == other._index;
}

template <typename T>
const T& ConstIterator<T>::operator*() const {
    _index_check("ConstIterator doens't in data bounds, while executing const operator*");
    SharedPtr<MatrixRow<T>[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols][_index % _cols];
}

template <typename T>
const T& ConstIterator<T>::value() const {
    return operator*();
}

template <typename T>
const T* ConstIterator<T>::operator->() const {
    _index_check("ConstIterator doens't in data bounds, while executing const operator->");
    SharedPtr<MatrixRow<T>[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

template <typename T>
const ConstIterator<T>& ConstIterator<T>::operator++() const {
    if (_index < _cols * _rows)
        ++_index;
    return *this;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::next() const {
    return operator++();
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) const {
    ConstIterator<T> it(*this);
    ++(*this);
    return it;
}

template <typename T>
bool ConstIterator<T>::operator<(ConstIterator const& other) const {
    return _index < other._index;
}

template <typename T>
bool ConstIterator<T>::is_end() const {
    return _index == _rows * _cols;
}

template <typename T>
ConstIterator<T>::operator bool() const {
    return _data.expired();
}

template <typename T>
bool ConstIterator<T>::is_valid() const {
    return _data.expired();
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator+(const int value) const {
    ConstIterator<T> it(*this);
    if (value < 0 && it._index < static_cast<size_t>(-value))
        it._index = 0;
    else
        it._index += value;

    if (it._index > _rows * _cols)
        it._index = _rows * _cols;

    return it;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator-(const int value) const {
    return operator+(-value);
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator+=(const int value) const {
    _index += value;
    return *this;
}
