template <typename T>
void Matrix<T>::_checkIndex(const size_t pos, const size_t limit) {
    if (pos > limit) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw IndexError(asctime(curtime), __FILE__, __LINE__, "Index is bigger than sizes");
    }
}

template <typename T>
void Matrix<T>::_moveRow(const size_t from, const size_t to) {
    auto tmp = _data[from];
    for (size_t i = from; i > to; --i)
        _data[i] = _data[i - 1];
    for (size_t i = from; i < to; ++i)
        _data[i] = _data[i + 1];
    _data[to] = tmp;
}

template <typename T>
void Matrix<T>::_moveCol(const size_t from, const size_t to) {
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
SharedPtr<MatrixRow<T>[]> Matrix<T>::_allocateMemory(const size_t rows, const size_t cols) {
    SharedPtr< MatrixRow<T>[] > data = nullptr;
    try {
        data.reset(new MatrixRow<T>[rows]);
        for (size_t i = 0; i < rows; i++)
            data[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc &err) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw MemoryError(asctime(curtime), __FILE__, __LINE__, "resizeRows error");
    }

    return data;
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns): BaseMatrix(rows, columns) {
    _data = _allocateMemory(rows, columns);
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns, const T &filler): BaseMatrix(rows, columns) {
    _data = _allocateMemory(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = filler;
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list) {
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &ilist: init_list)
        if (ilist.size() != cols) {
            time_t cur_time = time(NULL);
            auto curtime = localtime(&cur_time);
            throw InvalidArgument(asctime(curtime), __FILE__, __LINE__, "Bad initializer list");
        }

    _rows = rows;
    _cols = cols;
    _data = _allocateMemory(rows, cols);
    size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            _data[i / rows][i % rows] = elem;
            ++i;
        }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &matrix): BaseMatrix(matrix._rows, matrix._cols) {
    _data = _allocateMemory(matrix._rows, matrix._cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
}

template<typename T>
Matrix<T>::Matrix(const Matrix &&matrix): BaseMatrix(matrix._rows, matrix._cols) {
    _data = matrix._data;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix) {
    _data = _allocateMemory(matrix._rows, matrix._cols);
    return _data;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &&matrix) {
    _data = matrix._data;
    return _data;
}

template<typename T>
void Matrix<T>::fill(const Iterator<T> &start, const Iterator<T> &end, const T &value) {
    for (auto it = start; it < end; ++it)
        *it = value;
}

template<typename T>
void Matrix<T>::reverse(const Iterator<T> &start, const Iterator<T> &end) {
    auto end_it = end;
    --end_it;
    for (auto it = start; it < end_it; ++it, --end_it)
    {
        auto tmp = *it;
        *it = *end_it;
        *end_it = tmp;
    }
}

template<typename T>
void Matrix<T>::transpose() {
    auto tmp = _allocateMemory(_cols, _rows);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[j][i] = _data[i][j];

    _data = tmp;
    std::swap(_rows, _cols);
}

template<typename T>
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

template<typename T>
void Matrix<T>::resizeRows(size_t new_size, const T &filler) {
    resize(new_size, _cols, filler);
}

template<typename T>
void Matrix<T>::resizeCols(size_t new_size, const T &filler) {
    resize(_rows, new_size, filler);
}

template<typename T>
void Matrix<T>::insertRow(const size_t pos, const T &filler) {
    _checkIndex(pos, _rows);

    resizeRows(_rows + 1);
    fill(end() - static_cast<int>(_cols), end(), filler);
    _moveRow(_rows - 1, pos);
}

template<typename T>
void Matrix<T>::insertCol(const size_t pos, const T &filler) {
    _checkIndex(pos, _cols);

    resizeCols(_cols + 1);
    for (size_t i = 0; i < _rows; i++)
        _data[i][_cols - 1] = filler;
    _moveCol(_cols - 1, pos);

}

template<typename T>
void Matrix<T>::deleteRow(const size_t pos) {
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

template<typename T>
void Matrix<T>::deleteCol(const size_t pos) {
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

template<typename T>
bool Matrix<T>::operator==(const Matrix& matrix) const {
    if ((_rows != matrix._rows) || (_cols != matrix._cols))
        return false;

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            if (_data[i][j] != matrix[i][j])
                return false;

    return true;

}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& matrix) const {
    return !operator==(matrix);
}

template<typename T>
MatrixRow<T> Matrix<T>::operator[](const size_t row) {
    return _data[row];
}

template<typename T>
const MatrixRow<T> Matrix<T>::operator[](const size_t row) const {
    return _data[row];
}

template<typename T>
T &Matrix<T>::at(const size_t row, const size_t col) {
    return _data[row][col];
}

template<typename T>
const T &Matrix<T>::at(const size_t row, const size_t col) const {
    return _data[row][col];
}

template<typename T>
T &Matrix<T>::operator()(const size_t row, const size_t col) {
    return _data[row][col];
}

template<typename T>
const T &Matrix<T>::operator()(const size_t row, const size_t col) const {
    return _data[row][col];
}

template<typename T>
Iterator<T> Matrix<T>::begin() {
    return Iterator<T>(*this, 0);
}

template<typename T>
Iterator<T> Matrix<T>::end() {
    return Iterator<T>(*this, _cols * _rows);
}

template<typename T>
const Iterator<T> Matrix<T>::begin() const {
    return Iterator<T>(*this, 0);
}

template<typename T>
const Iterator<T> Matrix<T>::end() const {
    return Iterator<T>(*this, _cols * _rows);
}


template<typename T>
const Iterator<T> Matrix<T>::cbegin() {
    return Iterator<T>(*this, 0);
}

template<typename T>
const Iterator<T> Matrix<T>::cend() {
    return Iterator<T>(*this, _cols * _rows);
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix) {
    bool first_row = true;
    bool first_col = true;

    for (size_t i = 0; i < matrix.GetRows(); ++i) {
        first_col = true;
        if (!first_row)
            out << "\n";
        first_row = false;

        for(size_t j = 0; j < matrix.GetColumns(); ++j) {
            if (!first_col)
                out << '\t';
            first_col = false;
            out << matrix[i][j];
        }
    }
    return out;
}

