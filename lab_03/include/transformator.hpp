#pragma once

#include "matrix.hpp"
#include "exception.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include "direction.hpp"
#include "strategy.hpp"

class Point;
class BaseTransformStrategy;

class BaseTransformator {
public:
    // strategy
    virtual Point transform(const Point &p) = 0;
    virtual void setStrategy(shared_ptr<BaseTransformStrategy> strat) = 0;
};


class MyTransformator: public BaseTransformator {
protected:
    shared_ptr<BaseTransformStrategy> _strat;
public:
    MyTransformator() = delete;
    MyTransformator(const MyTransformator &) = delete;
    MyTransformator &operator=(const MyTransformator &) = delete;
    MyTransformator(shared_ptr<BaseTransformStrategy>);
    virtual Point transform(const Point &p) override;
    virtual void setStrategy(shared_ptr<BaseTransformStrategy> strat) override;
};
