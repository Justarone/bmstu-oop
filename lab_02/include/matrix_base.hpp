#pragma once
#include <cstddef>

class BaseMatrix {
public:
    BaseMatrix(const size_t rows = 0, const size_t columns = 0): _rows(rows), _cols(columns) {}

    virtual size_t GetColumns() const noexcept { return _cols; };
    virtual size_t GetRows() const noexcept { return _rows; };
    virtual operator bool() const noexcept { return _cols && _rows; }

    virtual ~BaseMatrix() {};

protected:
    size_t _rows = 0, _cols = 0;
};

