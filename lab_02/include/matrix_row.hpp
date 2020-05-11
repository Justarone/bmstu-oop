#pragma once
#include <memory>
#include "exception.hpp"

template<typename T>
using SharedPtr = std::shared_ptr<T>;

// внести в класс матрицы
template<typename Type>
class MatrixRow {
private:
    SharedPtr<Type[]> _data = nullptr;
    size_t _size = 0;
public:
    MatrixRow(Type *data, const size_t size): _data(data), _size(size) {}
    MatrixRow(): _data(nullptr), _size(0) {}
    Type &operator[](const size_t index);
    const Type &operator[](const size_t index) const;
    void reset(Type *data, const size_t size);
    void reset();
    Type *getAddr();
    const Type *getAddr() const;
};

#include "../implementation/matrix_row.hpp"
