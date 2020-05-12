template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns): BaseMatrix(rows, columns) {
    _data = _allocateMemory(rows, columns);
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T &filler): BaseMatrix(rows, columns) {
    _data = _allocateMemory(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = filler;
}

template <typename T>
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

    _data = _allocateMemory(rows, cols);
    _rows = rows;
    _cols = cols;
    size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
}

template <typename T>
static void _checkPtr(T ptr) {
    if (!ptr) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw InvalidArgument(asctime(curtime), __FILE__, __LINE__, "nullptr as a ptr of c-matrix");
    }
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T **matrix): BaseMatrix(rows, columns) {
    _checkPtr(matrix);
    _data = _allocateMemory(rows, columns);
    for (size_t i = 0; i < rows; ++i)
    {
        _checkPtr(matrix[i]);
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = matrix[i][j];
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix &matrix): BaseMatrix(matrix._rows, matrix._cols) {
    _data = _allocateMemory(matrix._rows, matrix._cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix &&matrix): BaseMatrix(matrix._rows, matrix._cols) {
    _data = matrix._data;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix) {
    _data = _allocateMemory(matrix._rows, matrix._cols);
    _rows = matrix._rows, _cols = matrix._cols;
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&matrix) {
    _data = matrix._data;
    _rows = matrix._rows, _cols = matrix._cols;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<T> > init_list) {
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &ilist: init_list)
        if (ilist.size() != cols) {
            time_t cur_time = time(NULL);
            auto curtime = localtime(&cur_time);
            throw InvalidArgument(asctime(curtime), __FILE__, __LINE__, "Bad initializer list");
        }

    _data.resize(rows, cols);
    size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
}

