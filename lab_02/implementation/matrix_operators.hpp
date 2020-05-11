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
T &Matrix<T>::operator()(size_t row, size_t col) {
    return _data[row][col];
}

template <typename T>
const T &Matrix<T>::operator()(size_t row, size_t col) const {
    return _data[row][col];
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
Matrix<T> Matrix<T>::operator/(const Matrix &matrix) const {
    Matrix<T> tmp(matrix);
    tmp.inverse();
    return operator*(tmp);
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const Matrix &matrix) {
    Matrix<T> tmp = operator/(matrix);
    *this = tmp;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() {
    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp = -_data[i][j];
    return tmp;
}

// NON-MEMBERS OPERATORS!
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


