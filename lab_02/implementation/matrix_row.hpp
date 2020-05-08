template<typename T>
Type &MatrixRow<T>::operator[](const size_t index) {
    if (index >= _size) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);
        throw IndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect column");
    }

    return _data[index];
}

template<typename T>
const Type &MatrixRow<T>::operator[](const size_t index) const {
    if (index >= _size) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);
        throw IndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect column");
    }

    return _data[index];
}

template<typename T>
void MatrixRow<T>::reset(const T *const data, const size_t size) {
    _size = size;
    _data.reset(data);
}

template<typename T>
void MatrixRow<T>::reset() {
    _size = 0;
    _data.reset(nullptr);
}

template<typename T>
Type *MatrixRow<T>::getAddr() {
    return _data.get();
}

template<typename T>
const Type * MatrixRow<T>::getAddr() const {
    return _data.get();
}
