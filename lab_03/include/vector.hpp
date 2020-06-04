#pragma once

#include <cstddef>
#include <memory>
#include "exception.hpp"

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using weak_ptr = std::weak_ptr<T>;

template <typename T>
class VecIterator;

template <typename T>
class ConstIterator;

class BaseVector {
protected:
    size_t _size;
public:
    virtual size_t size() { return _size; }
    virtual bool isEmpty() { return _size == 0; }
    virtual ~BaseVector() = 0;
};

BaseVector::~BaseVector() {}


template <typename Type>
class Vector: public BaseVector {
    shared_ptr<Type[]> _data;
    // size_t _size; // inherits
    void _allocateMemory(size_t size);
public:
    Vector();
    Vector(size_t size);
    Vector(Vector &);
    void push_back(Type elem);
    void erase(VecIterator<Type>);
    Type &operator[](size_t index);

    VecIterator<Type> begin();
    ConstIterator<Type> begin() const;
    VecIterator<Type> end();
    ConstIterator<Type> end() const;

};

template <typename T>
class VecIterator: public std::iterator<std::random_access_iterator_tag, T> {
    size_t _index = 0;
    size_t _size = 0;
    weak_ptr<T[]> _data;
public:
    VecIterator();
    VecIterator(shared_ptr<T[]> data, size_t size, size_t index = 0);
    VecIterator(VecIterator<T> &) = default;
    VecIterator<T> &operator=(VecIterator<T> &) = default;

    bool operator!=(const VecIterator<T> &vec) const { return _index == vec._index; }

    T *operator->();
    const T *operator->() const;
    T &operator*();
    const T &operator*() const;

    VecIterator<T> &operator++();
    VecIterator<T> operator++(int);
    VecIterator<T> &operator--();
    VecIterator<T> operator--(int);

    VecIterator<T> operator+(size_t diff) const;
    VecIterator<T> operator-(size_t diff) const;
};

template <typename T>
class ConstIterator: public std::iterator<std::random_access_iterator_tag, T> {
    mutable size_t _index = 0;
    size_t _size = 0;
    weak_ptr<T[]> _data;
public:
    ConstIterator() = delete;
    ConstIterator(ConstIterator<T> &) = default;
    ConstIterator(shared_ptr<T[]> data, size_t size, size_t index = 0);
    VecIterator<T> &operator=(ConstIterator<T> &) = default;

    bool operator!=(const ConstIterator<T> &vec) const { return _index == vec._index; }

    const T *operator->() const;
    const T &operator*() const;

    ConstIterator<T> &operator++() const;
    ConstIterator<T> operator++(int) const;
    ConstIterator<T> &operator--() const;
    ConstIterator<T> operator--(int) const;

    ConstIterator<T> operator+(size_t diff) const;
    ConstIterator<T> operator-(size_t diff) const;
};

#include "implementation/vector.hpp"
#include "implementation/iterator.hpp"
