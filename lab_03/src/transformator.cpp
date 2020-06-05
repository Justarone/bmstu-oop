#include "transformator.hpp"
#include "point.hpp"

MyTransformator::MyTransformator(shared_ptr<BaseTransformStrategy> strat): _strat(strat) {};

Point MyTransformator::transform(const Point &p) {
    return _strat->transform(p);
}

void MyTransformator::setStrategy(shared_ptr<BaseTransformStrategy> strat) {
    _strat = strat;
};
