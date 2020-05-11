template <typename T>
void Matrix<T>::_checkSizes(const Matrix<T> &matrix) const {
    if (_rows != matrix._rows || _cols != matrix._cols) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw IncompatibleElements(asctime(curtime), __FILE__, __LINE__, "Different matrix sizes");
    }
}

template <typename T>
void Matrix<T>::_checkMultSizes(const Matrix<T> &matrix) const {
    if (_cols != matrix._rows) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw IncompatibleElements(asctime(curtime), __FILE__, __LINE__,
                "Bad sizes of matrices for multiplication");
    }
}

template <typename T>
void Matrix<T>::_checkIndex(size_t pos, size_t limit) const {
    if (pos > limit) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw IndexError(asctime(curtime), __FILE__, __LINE__, "Index is bigger than sizes");
    }
}

template <typename T>
void Matrix<T>::_moveRow(size_t from, size_t to) {
    auto tmp = _data[from];
    for (size_t i = from; i > to; --i)
        _data[i] = _data[i - 1];
    for (size_t i = from; i < to; ++i)
        _data[i] = _data[i + 1];
    _data[to] = tmp;
}

template <typename T>
void Matrix<T>::_moveCol(size_t from, size_t to) {
    for (size_t j = 0; j < _rows; ++j)
    {
        auto tmp = _data[j][from];
        for (size_t i = from; i > to; --i)
            _data[j][i] = _data[j][i - 1];
        for (size_t i = from; i < to; ++i)
            _data[j][i] = _data[j][i + 1];
        _data[j][to] = tmp;
    }
}

template <typename T>
SharedPtr<typename Matrix<T>::MatrixRow[]> Matrix<T>::_allocateMemory(size_t rows, size_t cols) {
    SharedPtr< MatrixRow[] > data = nullptr;
    try {
        data.reset(new MatrixRow[rows]);
        for (size_t i = 0; i < rows; i++)
            data[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc &err) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw MemoryError(asctime(curtime), __FILE__, __LINE__, "_allocateMemory function error");
    }

    return data;
}


