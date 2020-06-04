#include "link.hpp"

Link::Link(size_t l1, size_t l2): _l1(l1), _l2(l2) {}
size_t Link::getFirst() const {
    return _l1;
}
size_t Link::getSecond() const {
    return _l2;
}

void Link::setFirst(size_t value) {
    _l1 = value;
}
void Link::setSecond(size_t value) {
    _l2 = value;
}
