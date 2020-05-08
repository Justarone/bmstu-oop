#pragma once
#include <memory>

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename Type>
class MatrixRow {
private:
    SharedPtr<Type[]> _data = nullptr;
    size_t _size = 0;
public:
    MatrixRow(const Type *const data, const size_t size): _data(data), _size(size) {}
    MatrixRow(): _data(nullptr), _size(0) {}
    Type &operator[](const size_t index);
    const Type &operator[](const size_t index) const;
    void reset(const Type *const data, const size_t size);
    void reset();
    Type *getAddr();
    const Type *getAddr() const;
};

