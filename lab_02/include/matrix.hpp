#pragma once
#include <iostream>
#include <iterator>
#include <memory>
#include "matrix_base.hpp"
#include "matrix_row.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"
#include "exception.hpp"

template <typename Type>
using SharedPtr = std::shared_ptr<Type>;
using string = std::string;

template <typename Type>
class Matrix: public BaseMatrix {
    friend Iterator<Type>;
    friend ConstIterator<Type>;
public:

    Matrix(const size_t rows = 0, const size_t columns = 0);
    Matrix(const size_t rows, const size_t columns, const Type &filler);
    Matrix(std::initializer_list<std::initializer_list<Type> > init_list);
    Matrix(const Matrix &matrix);
    Matrix(const Matrix &&matrix);

    virtual ~Matrix() = default;

    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(const Matrix &&matrix);

    ConstIterator<Type> begin() const;
    ConstIterator<Type> end() const;
    Iterator<Type> begin();
    Iterator<Type> end();
    ConstIterator<Type> cbegin() const;
    ConstIterator<Type> cend() const;

    void insert(Iterator<Type> start, const Iterator<Type> &end, const Type &value);
    void insert(Iterator<Type> start, Iterator<Type> source_start, const Iterator<Type> &source_end);
    void insert(Iterator<Type> start, ConstIterator<Type> source_start, const ConstIterator<Type> &source_end);
    void reverse(Iterator<Type> start, Iterator<Type> end);
    void transpose();

    void resize(size_t new_rows, size_t new_cols, const Type &filler = {});
    void resizeRows(size_t new_size, const Type &filler = {});
    void resizeCols(size_t new_size, const Type &filler = {});

    void insertRow(const size_t pos, const Type &filler = {});
    void insertCol(const size_t pos, const Type &filler = {});

    void deleteRow(const size_t pos);
    void deleteCol(const size_t pos);

    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;

    MatrixRow<Type> operator[](const size_t row);
    const MatrixRow<Type> operator[](const size_t row) const;
    Type &at(const size_t row, const size_t col);
    const Type &at(const size_t row, const size_t col) const;
    Type &operator()(const size_t row, const size_t col);
    const Type &operator()(const size_t row, const size_t col) const;


private:
    SharedPtr<MatrixRow<Type>[]> _data { nullptr };
    SharedPtr<MatrixRow<Type>[]> _allocateMemory(const size_t rows, const size_t cols);
    void _moveRow(const size_t from, const size_t to);
    void _moveCol(const size_t from, const size_t to);
    void _checkIndex(const size_t pos, const size_t limit);
};

#include "../implementation/matrix.hpp"

