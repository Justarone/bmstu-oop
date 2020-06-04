#pragma once

#include <cstddef>

class Link {
    size_t _l1, _l2;
public:
    Link(size_t l1, size_t l2);
    size_t getFirst() const;
    size_t getSecond() const;

    void setFirst(size_t value);
    void setSecond(size_t value);
};
