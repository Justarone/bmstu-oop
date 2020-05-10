#include <cstddef>

class BaseMatrix {
public:
    BaseMatrix(const size_t rows = 0, const size_t columns = 0): _rows(rows), _cols(columns) {}

    size_t GetColumns() const noexcept { return _cols; };
    size_t GetRows() const noexcept { return _rows; };
    operator bool() const noexcept { return _cols && _rows; }

    virtual ~BaseMatrix() {};

protected:
    size_t _rows = 0, _cols = 0;
};

