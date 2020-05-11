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
bool Matrix<T>::isSquare() const { return _rows == _cols; }

