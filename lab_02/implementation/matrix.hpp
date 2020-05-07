template <typename T>
SharedPtr<SharedPtr<T[]>[]> Matrix<T>::_allocate_memory(const size_t rows, const size_t cols) {
    SharedPtr<SharedPtr<T[]>[]> data = nullptr;
    try {
    data.reset(new SharedPtr<T[]>[rows]);
    for (size_t i = 0; i < rows; i++)
        data[i].reset(new T[cols]());
    }
    catch (std::bad_alloc &err) {
        auto cur_time = time(NULL);
        throw MemoryError(std::ctime(cur_time), __FILE__, __LINE__, "resizeRows error");
    }

    return data;
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns): BaseMatrix(rows, columns) {
    _data = _allocate_memory(rows, columns);
}

template<typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns, const T &filler): BaseMatrix(rows, columns) {
    _data = _allocate_memory(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            _data.get()[i].get()[j] = filler;
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list) {

    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &ilist: init_list)
        if (ilist.size() != cols)
            throw std::exception();

    _rows = rows;
    _cols = cols;
    _data = _allocate_memory(rows, cols);
    size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            _data.get()[i / rows].get()[i % rows] = elem;
            ++i;
        }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &matrix): BaseMatrix(matrix._rows, matrix._cols) {
    _data = _allocate_memory(matrix._rows, matrix._cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data.get()[i].get()[j] = matrix[i].get()[j];
}

template<typename T>
Matrix<T>::Matrix(const Matrix &&matrix): BaseMatrix(matrix._rows, matrix._cols) {
    _data = matrix._data;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix) {
    _data = _allocate_memory(matrix._rows, matrix._cols);
    return _data;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &&matrix) {
    _data = matrix._data;
    return _data;
}

template<typename T>
void Matrix<T>::fill(Iterator<T> start, Iterator<T> end, const T &value) {
    for (auto it = start; it < end; ++it)
        *it = value;
}

template<typename T>
void Matrix<T>::reverse(Iterator<T> start, Iterator<T> end) {
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
    size_t rows = _cols;
    size_t cols = _rows;
    Matrix<T> tmp(_cols, _rows);

}

template<typename T>
void Matrix<T>::resizeRows(const size_t new_size) {
    SharedPtr<SharedPtr<Type[]>[]> tmp = _allocate_memory(new_size, _cols);

    for (size_t i = 0; i < std::min(_rows, new_size); ++i)
        for (size_t j = 0; j < _cols, ++j)
            tmp[i][j] = _data[i][j];

    _data = tmp;
}

template<typename T>
void Matrix<T>::resizeCols(const size_t new_size) {
    SharedPtr<SharedPtr<Type[]>[]> tmp = _allocate_memory(_rows, new_size);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < std::min(new_size, _cols), ++j)
            tmp[i][j] = _data[i][j];

    _data = tmp;
}

template<typename T>
void Matrix<T>::insertRow(const size_t pos) {
    std::cout << "insertRow..." << std::endl;
}

template<typename T>
void Matrix<T>::insertRow(const size_t pos, const T &filler) {
    std::cout << "insertRow with filler..." << std::endl;
}

template<typename T>
void Matrix<T>::insertCol(const size_t pos) {
    std::cout << "insertCol..." << std::endl;
}

template<typename T>
void Matrix<T>::insertCol(const size_t pos, const T &filler) {
    std::cout << "insertCol with filler..." << std::endl;
}

template<typename T>
void Matrix<T>::deleteRow(const size_t pos) {
    std::cout << "deleteRow..." << std::endl;
}

template<typename T>
void Matrix<T>::deleteCol(const size_t pos) {
    std::cout << "deleteCol..." << std::endl;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& matrix) const {
    if (_rows != matrix._rows || _cols != matrix._cols)
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
T* Matrix<T>::operator[](const size_t row) {
    return _data[row];
}

template<typename T>
const T* Matrix<T>::operator[](const size_t row) const {
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
const Iterator<T> Matrix<T>::begin() const {
    return Iterator<T>(_data, 0, _rows, _cols);
}

template<typename T>
const Iterator<T> Matrix<T>::end() const {
    return Iterator<T>(_data, _rows * _cols, _rows, _cols);
}

ostream &operator<<(ostream &out, const Matrix &matrix) {
    bool first = true;
    bool first_col = true;
    for (size_t i = 0; i < matrix.GetRows(); ++i) {
        first_col = true;
        if (!first)
            out << std::endl;
        first = false;
        for(size_t j = 0; j < matrix.GetColumns(); ++j) {
            if (!first_col)
                out << ' ';
            first_col = false;
            out << matrix[i][j];
        }
    }
    return out;
}
