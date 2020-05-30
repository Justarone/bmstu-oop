template <size_t N, typename T>
void Matrix<N, T>::resetMatrix() {
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
            _data[i][j] = i == j ? 1 : 0;
}


template <size_t N, typename T>
void Matrix<N, T>::mulRight(const Matrix<N, T> &matrix) {
    T res[N][N];
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
            for (size_t k = 0; k < N; ++k)
                res[i][j] = _data[i][k] * matrix.at(k, j);

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
            _data[i][j] = res[i][j];
}


template <size_t N, typename T>
Matrix<N, T>::Matrix(const std::initializer_list<T> &init_list) {
    if (init_list.size() != N * N)
        throw AppInvalidArgument("Bad initializer_list");
    auto it = init_list.begin();

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
            _data[i][j] = *it++;
}


template <size_t N, typename T>
Matrix<N, T>::Matrix() {
    resetMatrix();
}


template <size_t N, typename T>
T &Matrix<N, T>::at(size_t row, size_t column) {
    if (row >= N || column >= N)
        throw AppOutOfRange("matrix at error (out of range)");
    return _data[row][column];
}


template <size_t N, typename T>
const T &Matrix<N, T>::at(size_t row, size_t column) const {
    if (row >= N || column >= N)
        throw AppOutOfRange("matrix at error (out of range)");
    return _data[row][column];
}


template <size_t N, typename T>
T &MathVec<N, T>::at(size_t pos) {
    if (pos >= N)
        throw AppOutOfRange("math vector at method error (out of range)");
    return _data[pos];
}

template <size_t N, typename T>
const T &MathVec<N, T>::at(size_t pos) const {
    if (pos >= N)
        throw AppOutOfRange("math vector at method error (out of range)");
    return _data[pos];
}

template <size_t N, typename T>
void MathVec<N, T>::resetVec() {
    for (size_t i = 0; i < N - 1; ++i)
        _data[i] = 0;
    _data[N - 1] = 1;
}


template <size_t N, typename T>
MathVec<N, T>::MathVec() {
    resetVec();
}

template <size_t N, typename T>
void MathVec<N, T>::mulLeft(const Matrix<N, T> &matrix) {
    MathVec<N, T> resVec;
    for (size_t i = 0; i < N; ++i)
    {
        resVec.at(i) = 0;
        for (size_t j = 0; j < N; ++j)
            resVec.at(i) += _data[j] * matrix.at(i, j);
    }

    for (size_t i = 0; i < N; ++i)
        _data[i] = resVec.at(i);
}

template <size_t N, typename T>
MathVec<N, T>::MathVec(const std::initializer_list<T> &init_list) {
    if (init_list.size() != N)
        throw AppInvalidArgument("error with init_list in MathVec constructor");

    auto it = init_list.begin();
    for (size_t i = 0; i < N; ++i)
        _data[i] = *it++;
}
