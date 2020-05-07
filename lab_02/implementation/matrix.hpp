template <typename T>
SharedPtr<SharedPtr<T[]>[]> Matrix<T>::_allocate_memory(const size_t rows, const size_t cols) {
    SharedPtr<SharedPtr<T[]>[]> data(new SharedPtr<T[]>[rows]());
    for (size_t i = 0; i < rows; i++)
        data.get()[i].reset(new T[rows]);
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
    std::cout << "transpose..." << std::endl;
}

template<typename T>
void Matrix<T>::resizeRows(const size_t new_size) {
    std::cout << "resizeRows..." << std::endl;
}

template<typename T>
void Matrix<T>::resizeRows(const size_t new_size, const T &filler) {
    std::cout << "resizeRows with two args..." << std::endl;
}

template<typename T>
void Matrix<T>::resizeCols(const size_t new_size) {
    std::cout << "resizeCols..." << std::endl;
}

template<typename T>
void Matrix<T>::resizeCols(const size_t new_size, const T &filler) {
    std::cout << "resizeCols with two cols..." << std::endl;
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
    std::cout << "operator==" << std::endl;
    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& matrix) const {
    std::cout << "operator!=" << std::endl;
    return false;
}

template<typename T>
T* Matrix<T>::operator[](const size_t row) {
    std::cout << "operator[]..." << std::endl;
    return _data.get()[row].get();
}

template<typename T>
const T* Matrix<T>::operator[](const size_t row) const {
    std::cout << "operator[] const..." << std::endl;
    return _data.get()[row].get();
}

template<typename T>
T &Matrix<T>::at(const size_t row, const size_t col) {
    std::cout << "at..." << std::endl;
    return _data.get()[row].get()[col];
}

template<typename T>
const T &Matrix<T>::at(const size_t row, const size_t col) const {
    std::cout << "const at..." << std::endl;
    return _data.get()[row].get()[col];
}

template<typename T>
const Iterator<T> Matrix<T>::begin() const {
    return Iterator<T>(_data, 0, _rows, _cols);
}

template<typename T>
const Iterator<T> Matrix<T>::end() const {
    return Iterator<T>(_data, _rows * _cols, _rows, _cols);
}
