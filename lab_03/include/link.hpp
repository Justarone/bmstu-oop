#pragma once

#include <cstddef>

class Link {
    size_t _l1, _l2;
public:
    size_t getFirst() {
        return _l1;
    }
    size_t getSecond() {
        return _l2;
    }

    void setFirst(size_t value) {
        _l1 = value;
    }
    void setSecond(size_t value) {
        _l2 = value;
    }
};
