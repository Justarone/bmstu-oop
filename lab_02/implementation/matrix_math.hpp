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
void Matrix<T>::transpose() {
    auto tmp = _allocateMemory(_cols, _rows);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[j][i] = _data[i][j];

    _data = tmp;
    std::swap(_rows, _cols);
}

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

