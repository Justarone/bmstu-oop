template <typename T>
bool Iterator<T>::operator!=(Iterator const& other) const {
    return _index != other._index;
}
template <typename T>
bool Iterator<T>::operator==(Iterator const& other) const {
    return _index == other._index;
}

template <typename T>
T& Iterator<T>::operator*() {
    if (_index >= _rows * _cols)
        throw std::out_of_range("out of range");
    SharedPtr<SharedPtr<T[]>[]> data_ptr = _data.lock();
    return data_ptr[_index / _rows][_index % _cols];
}

template <typename T>
const T& Iterator<T>::operator*() const {
    if (_index >= _rows * _cols)
        throw std::out_of_range("out of range");
    SharedPtr<SharedPtr<T[]>[]> data_ptr = _data;
    return data_ptr[_index / _rows][_index % _cols];
}

template <typename T>
T* Iterator<T>::operator->() {
    if (_index >= _rows * _cols)
        throw std::out_of_range("out of range");
    SharedPtr<SharedPtr<T[]>[]> data_ptr = _data;
    return data_ptr[_index / _rows][_index % _cols];
}

template <typename T>
const T* Iterator<T>::operator->() const {
    if (_index >= _rows * _cols)
        throw std::out_of_range("out of range");
    SharedPtr<SharedPtr<T[]>> data_ptr = _data;
    return _data[_index / _rows] + (_index % _cols);
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (_index < _cols * _rows)
        ++_index;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> it(*this);
    ++(*this);
    return it;
}

template <typename T>
bool Iterator<T>::operator<(Iterator const& other) const {
    return _index < other._index;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(const int value) {
    Iterator<T> it(*this);
    it._index += value;
    return it;
}

template <typename T>
Iterator<T> &Iterator<T>::operator+=(const int value) {
    _index += value;
    return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &it) {
    _data = it._data, _index = it._index, _rows = it._rows, _cols = it._cols;
    return *this;
}
