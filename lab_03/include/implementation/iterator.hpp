template <typename T>
VecIterator<T>::VecIterator() {};

template <typename T>
VecIterator<T>::VecIterator(shared_ptr<T[]> data, size_t size, size_t index):
    _data(data), _size(size), _index(index) {};

template <typename T>
T *VecIterator<T>::operator->() {
    if (_index >= _size)
        throw AppOutOfRange("Vector out of range iterator");
    if (_data.expired())
        throw AppBadState("No data under iterator");
    return _data.lock() + _index;
}

template <typename T>
const T *VecIterator<T>::operator->() const {
    if (_index >= _size)
        throw AppOutOfRange("Vector out of range iterator");
    if (_data.expired())
        throw AppBadState("No data under iterator");
    return _data.lock() + _index;
}

template <typename T>
T &VecIterator<T>::operator*() {
    if (_index >= _size)
        throw AppOutOfRange("Vector out of range iterator");
    if (_data.expired())
        throw AppBadState("No data under iterator");
    return _data.lock()[_index];
}

template <typename T>
const T &VecIterator<T>::operator*() const {
    if (_index >= _size)
        throw AppOutOfRange("Vector out of range iterator");
    if (_data.expired())
        throw AppBadState("No data under iterator");
    return _data.lock()[_index];
}

template <typename T>
VecIterator<T> &VecIterator<T>::operator++() {
    ++_index;
    return *this;
}

template <typename T>
VecIterator<T> VecIterator<T>::operator++(int) {
    VecIterator<T> it(*this);
    ++(*this);
    return it;
}

template <typename T>
VecIterator<T> &VecIterator<T>::operator--() {
    --_index;
    return *this;
}

template <typename T>
VecIterator<T> VecIterator<T>::operator--(int) {
    VecIterator<T> it(*this);
    --(*this);
    return it;
}

template <typename T>
VecIterator<T> VecIterator<T>::operator+(size_t diff) const {
    VecIterator<T> it(*this);
    it._index += diff;
    return it;
}

template <typename T>
VecIterator<T> VecIterator<T>::operator-(size_t diff) const {
    VecIterator<T> it(*this);
    it._index -= diff;
    return it;
}

template <typename T>
ConstIterator<T>::ConstIterator(shared_ptr<T[]> data, size_t size, size_t index):
    _data(data), _size(size), _index(index) {}

template <typename T>
const T *ConstIterator<T>::operator->() const {
    if (_index >= _size)
        throw AppOutOfRange("Vector out of range iterator");
    if (_data.expired())
        throw AppBadState("No data under iterator");
    return _data.lock() + _index;
}

template <typename T>
const T &ConstIterator<T>::operator*() const {
    if (_index >= _size)
        throw AppOutOfRange("Vector out of range iterator");
    if (_data.expired())
        throw AppBadState("No data under iterator");
    return _data.lock()[_index];
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator+(size_t diff) const {
    ConstIterator<T> it(*this);
    it._index += diff;
    return it;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator-(size_t diff) const {
    ConstIterator<T> it(*this);
    it._index -= diff;
    return it;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator++() const {
    ++_index;
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) const {
    ConstIterator<T> it(*this);
    ++(*this);
    return it;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator--() const {
    --_index;
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator--(int) const {
    ConstIterator<T> it(*this);
    --(*this);
    return it;
}
