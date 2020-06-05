#include "base_vector.hpp"

size_t BaseVector::size() const {
    return _size; 
}

bool BaseVector::isEmpty() const { 
    return _size == 0; 
}

BaseVector::~BaseVector() {}

