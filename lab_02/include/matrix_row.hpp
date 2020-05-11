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
    Type &operator[](const size_t index) {
        if (index >= _size) {
            time_t cur_time = time(NULL);
            auto local_time = localtime(&cur_time);
            throw IndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect column");
        }

        return _data[index];
    }

    const Type &operator[](const size_t index) const {
        if (index >= _size) {
            time_t cur_time = time(NULL);
            auto local_time = localtime(&cur_time);
            throw IndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect column");
        }

        return _data[index];
    }

    void reset(Type *data, const size_t size) {
        _size = size;
        _data.reset(data);
    }

    void reset() {
        _size = 0;
        _data.reset();
    }

    Type *getAddr() { return _data.get(); }
    const Type *getAddr() const { return _data.get(); }
};
