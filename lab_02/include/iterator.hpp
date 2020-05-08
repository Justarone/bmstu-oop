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
class Iterator: public std::iterator<std::input_iterator_tag, Type> {
public:
    Iterator(const Matrix<Type> &matrix, const size_t index = 0): _data(matrix._data), _index(index),
                                                                  _rows(matrix._rows), _cols(matrix._cols) {}
    Iterator(const Iterator& it) = default;

    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const;
    bool operator<(Iterator const& other) const;

    operator bool() const;
    bool is_end() const;
    bool is_valid() const;

    Iterator<Type> operator+(const int value) const;
    Iterator<Type> operator-(const int value) const;
    Iterator<Type> &operator+=(const int value);
    Iterator<Type> &operator=(const Iterator<Type> &it);

    Type& operator*();
    const Type& operator*() const;
    Type& value();
    const Type& value() const;

    Type* operator->();
    const Type* operator->() const;

    Iterator<Type>& operator++();
    Iterator<Type>& next();
    Iterator<Type> operator++(int);

private:
    void _index_check(const string hint = "");
    WeakPtr<MatrixRow<Type>[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

#include "../implementation/iterator.hpp"
