template <typename T>
void Matrix<T>::resize(size_t rows, size_t cols, const T &filler) {
    if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
        rows = 0, cols = 0;

    auto tmp = _allocateMemory(rows, cols);

    for (size_t i = 0; i < std::min(_rows, rows); ++i)
    {
        for (size_t j = 0; j < std::min(_cols, cols); ++j)
            tmp[i][j] = _data[i][j];
        for (size_t j = _cols; j < cols; ++j)
            tmp[i][j] = filler;
    }

    for (size_t i = _rows; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            tmp[i][j] = filler;

    _data = tmp;
    _rows = rows;
    _cols = cols;
}

template <typename T>
void Matrix<T>::resizeRows(size_t new_size, const T &filler) {
    resize(new_size, _cols, filler);
}

template <typename T>
void Matrix<T>::resizeCols(size_t new_size, const T &filler) {
    resize(_rows, new_size, filler);
}

template <typename T>
void Matrix<T>::insertRow(size_t pos, const T &filler) {
    _checkIndex(pos, _rows);

    resizeRows(_rows + 1);
    fill(end() - static_cast<int>(_cols), end(), filler);
    _moveRow(_rows - 1, pos);
}

template <typename T>
void Matrix<T>::insertCol(size_t pos, const T &filler) {
    _checkIndex(pos, _cols);

    resizeCols(_cols + 1);
    for (size_t i = 0; i < _rows; i++)
        _data[i][_cols - 1] = filler;
    _moveCol(_cols - 1, pos);

}

template <typename T>
void Matrix<T>::deleteRow(size_t pos) {
    _checkIndex(pos, _rows - 1);
    auto tmp = _allocateMemory(_rows - 1, _cols);
    
    size_t si = 0, di = 0;
    while (si < _rows) {
        if (si != pos) {
            for (size_t i = 0; i < _cols; ++i)
                tmp[di][i] = _data[si][i];
            ++di;
        }
        ++si;
    }

    _data = tmp;
    --_rows;
}

template <typename T>
void Matrix<T>::deleteCol(size_t pos) {
    _checkIndex(pos, _cols - 1);
    auto tmp = _allocateMemory(_rows, _cols - 1);
    
    size_t si = 0, di = 0;
    while (si < _cols) {
        if (si != pos) {
            for (size_t i = 0; i < _rows; ++i)
                tmp[i][di] = _data[i][si];
            ++di;
        }
        ++si;
    }

    _data = tmp;
    --_cols;
}


