#pragma once
#include <memory>
#include <string>

#include "exception.hpp"
#include "matrix_row.hpp"

template<typename T>
class Matrix;

template <typename T>
using SharedPtr = std::shared_ptr<T>;
template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename Type>
class ConstIterator: public std::iterator<std::bidirectional_iterator_tag, Type> {
public:
    ConstIterator(const Matrix<Type> &matrix, const size_t index = 0): _data(matrix._data), _index(index),
                                                                  _rows(matrix._rows), _cols(matrix._cols) {}
    ConstIterator(const ConstIterator& it) = default;

    bool operator!=(ConstIterator const& other) const;
    bool operator==(ConstIterator const& other) const;
    bool operator<(ConstIterator const& other) const;

    operator bool() const;
    bool is_end() const;
    bool is_valid() const;

    ConstIterator<Type> operator+(const int value) const;
    ConstIterator<Type> &operator+=(const int value) const;
    ConstIterator<Type> operator-(const int value) const;

    const Type& operator*() const;
    const Type& value() const;

    const Type* operator->() const;

    const ConstIterator<Type>& operator++() const;
    ConstIterator<Type>& next() const;
    ConstIterator<Type> operator++(int) const;

private:
    void _index_check(const string hint = "") const;
    WeakPtr<MatrixRow<Type>[]> _data = nullptr;
    mutable size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

#include "../implementation/const_iterator.hpp"
