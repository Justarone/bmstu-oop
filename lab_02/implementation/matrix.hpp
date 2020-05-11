template <typename T>
void Matrix<T>::_checkSizes(const Matrix<T> &matrix) const {
    if (_rows != matrix._rows || _cols != matrix._cols) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw IncompatibleElements(asctime(curtime), __FILE__, __LINE__, "Different matrix sizes");
    }
}

template <typename T> 
static void _excludeCopy(Matrix<T> &target, const Matrix<T> &source, size_t ex_row, size_t ex_col) {
    if (target.GetRows() != source.GetRows() - 1 || target.GetColumns() != source.GetColumns() - 1) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw IncompatibleElements(asctime(curtime), __FILE__, __LINE__, "Target has wrong size");
    }

    size_t row_index, col_index;
    for (size_t i = 0; i < source.GetRows() - 1; ++i)
        for (size_t j = 0; j < source.GetColumns() - 1; ++j) {
            row_index = i >= ex_row ? i + 1 : i;
            col_index = j >= ex_col ? j + 1: j;
            target[i][j] = source[row_index][col_index];
        }
}

template <typename T>
static T _determinant(const Matrix<T> &matrix) {
    if (matrix.GetRows() == 2)
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    if (matrix.GetRows() == 1)
        return matrix[0][0];

    Matrix<T> tmp(matrix.GetRows() - 1, matrix.GetColumns() - 1);
    T res = {};
    for (size_t i = 0; i < matrix.GetRows(); ++i) {
        _excludeCopy(tmp, matrix, 0, i);
        T minor = _determinant(tmp);
        if (i & 1)
            minor = -minor;
        res += minor * matrix[0][i];
    }

    return res;
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
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&matrix) {
    _data = matrix._data;
    _rows = matrix._rows, _cols = matrix._cols;
    return *this;
}

template <typename T>
void Matrix<T>::fill(Iterator<T> start, const Iterator<T> &end, const T &value) {
    for (auto it = start; it < end; ++it)
        *it = value;
}

template <typename T>
void Matrix<T>::fill(Iterator<T> start, Iterator<T> source_start, const Iterator<T> &source_end) {
    auto source_it = source_start;
    auto it = start;
    while (!it.isEnd() && source_it < source_end) {
        *it = *source_it;
        ++it, ++source_it;
    }
}

template <typename T>
void Matrix<T>::fill(Iterator<T> start, ConstIterator<T> source_start, const ConstIterator<T> &source_end) {
    auto source_it = source_start;
    auto it = start;
    while (!it.isEnd() && source_it < source_end) {
        *it = *source_it;
        ++it, ++source_it;
    }
}

template <typename T>
void Matrix<T>::reverseSeq(Iterator<T> start, Iterator<T> end) {
    end = end - 1;
    for (; start < end; start++, end = end - 1)
    {
        auto tmp = *start;
        *start = *end;
        *end = tmp;
    }
}

template <typename T>
void Matrix<T>::transpose() {
    auto tmp = _allocateMemory(_cols, _rows);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[j][i] = _data[i][j];

    _data = tmp;
    std::swap(_rows, _cols);
}

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

template <typename T>
bool Matrix<T>::operator==(const Matrix& matrix) const {
    if ((_rows != matrix._rows) || (_cols != matrix._cols))
        return false;

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            if (_data[i][j] != matrix[i][j])
                return false;

    return true;

}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& matrix) const {
    return !operator==(matrix);
}

template <typename T>
typename Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row) {
    return _data[row];
}

template <typename T>
const typename Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row) const {
    return _data[row];
}

template <typename T>
T &Matrix<T>::at(size_t row, size_t col) {
    return _data[row][col];
}

template <typename T>
const T &Matrix<T>::at(size_t row, size_t col) const {
    return _data[row][col];
}

template <typename T>
T &Matrix<T>::operator()(size_t row, size_t col) {
    return _data[row][col];
}

template <typename T>
const T &Matrix<T>::operator()(size_t row, size_t col) const {
    return _data[row][col];
}

template <typename T>
Iterator<T> Matrix<T>::begin() {
    return Iterator<T>(*this, 0);
}

template <typename T>
Iterator<T> Matrix<T>::end() {
    return Iterator<T>(*this, _cols * _rows);
}

template <typename T>
ConstIterator<T> Matrix<T>::begin() const {
    return ConstIterator<T>(*this, 0);
}

template <typename T>
ConstIterator<T> Matrix<T>::end() const {
    return ConstIterator<T>(*this, _cols * _rows);
}


template <typename T>
ConstIterator<T> Matrix<T>::cbegin() const {
    return ConstIterator<T>(*this, 0);
}

template <typename T>
ConstIterator<T> Matrix<T>::cend() const {
    return ConstIterator<T>(*this, _cols * _rows);
}

template <typename T>
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

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
    _checkSizes(matrix);
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + matrix[i][j];

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const {
    _checkSizes(matrix);
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + matrix[i][j];

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const { 
    _checkMultSizes(matrix);

    Matrix<T> tmp(_rows, matrix._cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < matrix._cols; ++j)
            for (size_t k = 0; k < _cols; ++k)
                tmp[i][j] += _data[i][k] * matrix[k][j];

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T &elem) const noexcept {
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + elem;

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T &elem) const noexcept {
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] - elem;

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &elem) const noexcept {
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] * elem;

    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &matrix) {
    _checkSizes(matrix);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] += matrix[i][j];

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &matrix) {
    _checkSizes(matrix);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] -= matrix[i][j];

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix &matrix) {
    _checkSizes(matrix);
    _checkMultSizes(matrix);

    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            for (size_t k = 0; k < _rows; ++k)
                tmp[i][j] += _data[i][k] + matrix[k][j];

    *this = tmp;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const T &elem) noexcept {
    for (auto &element: *this)
        element += elem;

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const T &elem) noexcept {
    for (auto &element: *this)
        element -= elem;

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const T &elem) noexcept {
    for (auto &element: *this)
        element *= elem;

    return *this;
}

template <typename T>
bool Matrix<T>::isSquare() const { return _rows == _cols; }

template <typename T>
T Matrix<T>::determinant() const {
    if (!isSquare()) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw InvalidState(asctime(curtime), __FILE__, __LINE__, "Matrix should be square to get determinant;");
    }

    return _determinant(*this);
}

template <typename T>
Matrix<T> Matrix<T>::addMatrix(const Matrix &matrix) const {
    return operator+(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::subMatrix(const Matrix &matrix) const {
    return operator-(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::mulMatrix(const Matrix &matrix) const {
    return operator*(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::addElem(const T &elem) const noexcept {
    return operator+(elem);
}

template <typename T>
Matrix<T> Matrix<T>::subElem(const T &elem) const noexcept {
    return operator-(elem);
}

template <typename T>
Matrix<T> Matrix<T>::mulElem(const T &elem) const noexcept {
    return operator*(elem);
}


template <typename T>
Matrix<T> &Matrix<T>::addEqMatrix(const Matrix &matrix) {
    return operator+=(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::subEqMatrix(const Matrix &matrix) {
    return operator-=(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::mulEqMatrix(const Matrix &matrix) {
    return operator*=(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::addEqElem(const T &elem) noexcept {
    return operator+=(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::subEqElem(const T &elem) noexcept {
    return operator-=(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::mulEqElem(const T &elem) noexcept {
    return operator*=(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const T &elem) {
    if (elem == 0) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw InvalidArgument(asctime(curtime), __FILE__, __LINE__, "Zero divisor");
    }

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] /= elem;

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::divEqElem(const T &elem) {
    return operator/=(elem);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T &elem) const {
    if (elem == 0) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw InvalidArgument(asctime(curtime), __FILE__, __LINE__, "Zero divisor");
    }

    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] =_data[i][j] / elem;

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::divElem(const T &elem) const {
    return operator/(elem);
}

template <typename T>
Matrix<T> Matrix<T>::operator-() {
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp = -_data[i][j];
    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::neg() {
    return operator-();
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

template <typename T>
void Matrix<T>::inverse() {
    T det = determinant();
    if (!isSquare() || !det) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw InvalidState(asctime(curtime), __FILE__, __LINE__, "Only square matrix can be inversed and determinant should be > 0");
    }

    Matrix<T> res(_rows, _cols);
    Matrix<T> tmp(_rows - 1, _cols - 1);
    T value = {};
    
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
        {
            _excludeCopy(tmp, *this, i, j);
            value = tmp.determinant() / det;
            if ((i + j) & 1)
                value = -value;
            res[j][i] = value;
        }

    *this = res;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix &matrix) const {
    Matrix<T> tmp(matrix);
    tmp.inverse();
    return operator*(tmp);
}

template <typename T>
Matrix<T> Matrix<T>::divMatrix(const Matrix &matrix) const {
    return operator/(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const Matrix &matrix) {
    Matrix<T> tmp = operator/(matrix);
    *this = tmp;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::divEqMatrix(const Matrix &matrix) {
    return operator/=(matrix);
}

template <typename T>
Matrix<T> operator+(const T &elem, const Matrix<T> &matrix) {
    return matrix + elem;
}

template <typename T>
Matrix<T> operator-(const T &elem, const Matrix<T> &matrix) {
    return matrix - elem;
}

template <typename T>
Matrix<T> operator*(const T &elem, const Matrix<T> &matrix) {
    return matrix * elem;
}

template <typename T>
Matrix<T> operator/(const T &elem, const Matrix<T> &matrix) {
    Matrix tmp(matrix);
    tmp.inverse();
    return tmp * elem;
}
