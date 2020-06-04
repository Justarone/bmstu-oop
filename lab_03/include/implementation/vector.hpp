template <typename T>
void Vector<T>::_allocateMemory(size_t size) {
    shared_ptr<T[]> tmp;
    try {
        tmp.reset(new T[size]);
    } catch(std::bad_alloc &) {
        throw AppMemoryError("Vector allocate memory error");
    }

    for (size_t i = 0; i < std::min(size, _size); i++)
        tmp[i] = _data[i];
    _data = tmp;
    _size = size;
}

template <typename T>
Vector<T>::Vector() {};

template <typename T>
Vector<T>::Vector(size_t size) {
    _allocateMemory(size);
}

template <typename T>
Vector<T>::Vector(Vector &vec) {
    _allocateMemory(vec.size());
    for (size_t i = 0; i < vec.size(); ++i)
        _data[i] = vec[i];
};

template <typename T>
T &operator[](size_t index) {
    if (index > _size)
        throw AppOutOfRange("Vector out of range elem");
    return _data[index];
};

template <typename T>
void Vector<T>::push_back(T elem) {
    _allocateMemory(_size + 1);
    _data[_size - 1] = elem;
}

template <typename T>
void Vector<T>::erase(VecIterator<T> di) {
    auto si = di + 1;
    while (si)
        *di++ = *si++;
    _allocateMemory(_size - 1);
}

template <typename T>
VecIterator<T> Vector<T>::begin() {
    return VecIterator<T>(_data, _size);
}

template <typename T>
ConstIterator<T> Vector<T>::begin() const {
    return ConstIterator<T>(_data, _size);
}

template <typename T>
VecIterator<T> Vector<T>::end() {
    return VecIterator<T>(_data, _size, _size);
}

template <typename T>
ConstIterator<T> Vector<T>::end() const {
    return ConstIterator<T>(_data, _size, _size);
}
