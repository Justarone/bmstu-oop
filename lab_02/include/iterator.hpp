#pragma once
#include <memory>

template <typename T>
using SharedPtr = std::shared_ptr<T>;
template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename Type>
class Iterator: public std::iterator<std::input_iterator_tag, Type> {
public:
    Iterator(const SharedPtr<SharedPtr<Type[]>[]> data, const size_t index, const size_t row_size,
            const size_t col_size): _data(data), _index(index), _rows(row_size), _cols(col_size) {}
    Iterator(const Iterator& it) = default;

    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const;
    bool operator<(Iterator const& other) const;

    Iterator<Type> operator+(const int value);
    Iterator<Type> &operator+=(const int value);
    Iterator<Type> &operator=(const Iterator<Type> &it);

    Type& operator*();
    const Type& operator*() const;

    Type* operator->();
    const Type* operator->() const;

    Iterator<Type>& operator++();
    Iterator<Type> operator++(int);

private:
    WeakPtr<SharedPtr<Type[]>[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

#include "../implementation/iterator.hpp"
