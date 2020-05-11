template <typename T>
T &Matrix<T>::at(size_t row, size_t col) {
    return _data[row][col];
}

template <typename T>
const T &Matrix<T>::at(size_t row, size_t col) const {
    return _data[row][col];
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
Matrix<T> &Matrix<T>::divEqElem(const T &elem) {
    return operator/=(elem);
}

template <typename T>
Matrix<T> Matrix<T>::divElem(const T &elem) const {
    return operator/(elem);
}

template <typename T>
Matrix<T> Matrix<T>::neg() {
    return operator-();
}

template <typename T>
Matrix<T> Matrix<T>::divMatrix(const Matrix &matrix) const {
    return operator/(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::divEqMatrix(const Matrix &matrix) {
    return operator/=(matrix);
}
