#include "strategy.hpp"


MoveStrategy::MoveStrategy(double x, double y, double z): _x(x), _y(y), _z(z) {}
ScaleStrategy::ScaleStrategy(double value): _value(value) {};
RotateStrategy::RotateStrategy(Direction dir, double value): _dir(dir), _value(value) {};


Point MoveStrategy::transform(const Point &p) {
    Matrix<4, double> moveMatrix = { 1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     _x, _y, _z, 1 };
    MathVec<4, double> resVec = { p.getX(), p.getY(), p.getZ(), 1 };
    resVec.mulRight(moveMatrix);
    return Point(resVec.at(0), resVec.at(1), resVec.at(2));
}

Point ScaleStrategy::transform(const Point &p) {
    Matrix<4, double> scaleMatrix = { _value, 0, 0, 0,
                                     0, _value, 0, 0,
                                     0, 0, _value, 0,
                                     0, 0, 0, 1 };
    MathVec<4, double> resVec = { p.getX(), p.getY(), p.getZ(), 1 };
    resVec.mulRight(scaleMatrix);
    return Point(resVec.at(0), resVec.at(1), resVec.at(2));
}

Point RotateStrategy::transform(const Point &p) {
    Matrix<4, double> rotateMatrix;

    if (_dir == Direction::X) {
        rotateMatrix.at(0, 0) = 1;
        rotateMatrix.at(2, 1) = -sin(_value);
        rotateMatrix.at(1, 1) = cos(_value);
        rotateMatrix.at(1, 2) = sin(_value);
        rotateMatrix.at(2, 2) = cos(_value);
    }
    else if (_dir == Direction::Y) {
        rotateMatrix.at(1, 1) = 1;
        rotateMatrix.at(0, 0) = cos(_value);
        rotateMatrix.at(0, 2) = sin(_value);
        rotateMatrix.at(2, 0) = -sin(_value);
        rotateMatrix.at(2, 2) = cos(_value);
    }
    else if (_dir == Direction::Z) {
        rotateMatrix.at(2, 2) = 1;
        rotateMatrix.at(0, 0) = cos(_value);
        rotateMatrix.at(0, 1) = sin(_value);
        rotateMatrix.at(1, 0) = -sin(_value);
        rotateMatrix.at(1, 1) = cos(_value);
    }
    MathVec<4, double> resVec = { p.getX(), p.getY(), p.getZ(), 1 };
    resVec.mulRight(rotateMatrix);
    return Point(resVec.at(0), resVec.at(1), resVec.at(2));
}
