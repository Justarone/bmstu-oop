template <typename T>
T &Matrix<T>::MatrixRow::operator[](size_t index) {
    if (index >= _size) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);
        throw IndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect column");
    }

    return _data[index];
}

template <typename T>
const T &Matrix<T>::MatrixRow::operator[](size_t index) const {
    if (index >= _size) {
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);
        throw IndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect column");
    }

    return _data[index];
}

template <typename T>
void Matrix<T>::MatrixRow::reset(T *data, const size_t size) {
    _size = size;
    _data.reset(data);
}

template <typename T>
void Matrix<T>::MatrixRow::reset() {
    _size = 0;
    _data.reset();
}


