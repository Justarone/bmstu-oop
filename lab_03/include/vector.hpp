#pragma once

#include <cstddef>
#include <memory>
#include "exception.hpp"
#include "base_vector.hpp"

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using weak_ptr = std::weak_ptr<T>;

template <typename T>
class VecIterator;

template <typename T>
class ConstIterator;


template <typename Type>
class Vector: public BaseVector {
    shared_ptr<Type[]> _data;
    // size_t _size; // inherits
    void _allocateMemory(size_t size);
public:
    Vector();
    Vector(size_t size);
    Vector(const Vector &);
    void push_back(Type elem);
    void erase(VecIterator<Type>);
    Type &operator[](size_t index);
    const Type &operator[](size_t index) const;

    VecIterator<Type> begin();
    ConstIterator<Type> begin() const;
    VecIterator<Type> end();
    ConstIterator<Type> end() const;

};

template <typename T>
class VecIterator: public std::iterator<std::random_access_iterator_tag, T> {
    weak_ptr<T[]> _data;
    size_t _size = 0;
    size_t _index = 0;
public:
    VecIterator();
    VecIterator(shared_ptr<T[]> data, size_t size, size_t index = 0);
    VecIterator(const VecIterator<T> &) = default;
    VecIterator(VecIterator<T> &&) = default;
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
    weak_ptr<T[]> _data;
    size_t _size = 0;
    mutable size_t _index = 0;
public:
    ConstIterator() = delete;
    ConstIterator(const ConstIterator<T> &) = default;
    ConstIterator(ConstIterator<T> &&) = default;
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
