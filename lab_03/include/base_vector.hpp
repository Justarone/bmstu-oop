#pragma once

#include <cstddef>

class BaseVector {
protected:
    size_t _size = 0;
public:
    virtual size_t size() const;
    virtual bool isEmpty() const;
    virtual ~BaseVector() = 0;
};

