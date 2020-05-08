template <typename T>
void Iterator<T>::_index_check(const string hint) {
    if (_index < _rows * _cols)
        return;
    time_t cur_time = time(NULL);
    auto local_time = localtime(&cur_time);
    throw IndexError(asctime(local_time), __FILE__, __LINE__, hint);
}

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
    _index_check("Iterator doens't in data bounds, while executing operator*");
    SharedPtr<MatrixRow<T>[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols][_index % _cols];
}

template <typename T>
T& Iterator<T>::value() {
    return operator*();
}

template <typename T>
const T& Iterator<T>::operator*() const {
    _index_check("Iterator doens't in data bounds, while executing const operator*");
    SharedPtr<MatrixRow<T>[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols][_index % _cols];
}

template <typename T>
const T& Iterator<T>::value() const {
    return operator*();
}

template <typename T>
T* Iterator<T>::operator->() {
    _index_check("Iterator doens't in data bounds, while executing operator->");
    SharedPtr<MatrixRow<T>[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

template <typename T>
const T* Iterator<T>::operator->() const {
    _index_check("Iterator doens't in data bounds, while executing const operator->");
    SharedPtr<MatrixRow<T>[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (_index < _cols * _rows)
        ++_index;
    return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::next() {
    return operator++();
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
bool Iterator<T>::is_end() const {
    return _index == _rows * _cols;
}

template <typename T>
Iterator<T>::operator bool() const {
    return _data.expired();
}

template <typename T>
bool Iterator<T>::is_valid() const {
    return _data.expired();
}

template <typename T>
Iterator<T> Iterator<T>::operator+(const int value) const {
    Iterator<T> it(*this);
    it._index += value;

    if (it._index < 0)
        it._index = 0;
    else if (it._index > _rows * _cols)
        it._index = _rows * _cols;

    return it;
}

template <typename T>
Iterator<T> Iterator<T>::operator-(const int value) const {
    return operator+(-value);
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
