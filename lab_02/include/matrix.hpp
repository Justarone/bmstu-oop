#pragma once
#include <iostream>
#include <new>
#include <vector>
#include <memory>
#include "iterator.hpp"
#include "exception.hpp"

template <typename Type>
using SharedPtr = std::shared_ptr<Type>;

class BaseMatrix {
public:
    BaseMatrix(const size_t rows = 0, const size_t columns = 0): _rows(rows), _cols(columns) {}
    virtual ~BaseMatrix() = default;

    size_t GetColumns() const noexcept { return _cols; };
    size_t GetRows() const noexcept { return _rows; };
    operator bool() const noexcept { return _cols && _rows; }

protected:
    size_t _rows = 0, _cols = 0;
};


template <typename Type>
class Matrix: public BaseMatrix {
    friend Iterator<Type>;
public:
    Matrix(const size_t rows = 0, const size_t columns = 0);
    Matrix(const size_t rows, const size_t columns, const Type &filler);
    Matrix(std::initializer_list<std::initializer_list<Type> > init_list);
    Matrix(const Matrix &matrix);
    Matrix(const Matrix &&matrix);

    virtual ~Matrix() = default;

    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(const Matrix &&matrix);

    const Iterator<Type> begin() const;
    const Iterator<Type> end() const;

    void fill(Iterator<Type> start, Iterator<Type> end, const Type &value);
    void reverse(Iterator<Type> start, Iterator<Type> end);
    void transpose();

    void resizeRows(const size_t new_size);
    void resizeCols(const size_t new_size);

    void insertRow(const size_t pos);
    void insertRow(const size_t pos, const Type &filler);
    void insertCol(const size_t pos);
    void insertCol(const size_t pos, const Type &filler);

    void deleteRow(const size_t pos);
    void deleteCol(const size_t pos);

    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;

    Type *operator[](const size_t row);
    const Type *operator[](const size_t row) const;
    Type &at(const size_t row, const size_t col);
    const Type &at(const size_t row, const size_t col) const;


private:
    SharedPtr<SharedPtr<Type[]>[]> _data { nullptr };
    SharedPtr<SharedPtr<Type[]>[]> _allocate_memory(const size_t rows, const size_t cols);
};

#include "../implementation/matrix.hpp"

    //void pushRowFront();
    //void pushRowFront(const Type &filler);
    //void pushColFront();
    //void pushColFront(const Type &filler);

    //void pushRowBack();
    //void pushRowBack(const Type &filler);
    //void pushColBack();
    //void pushColBack(const Type &filler);

    //void popRowFront();
    //void popColFront();

    //void popRowBack();
    //void popColBack();

