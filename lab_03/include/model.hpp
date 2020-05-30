#pragma once

#include <vector>
#include "link.hpp"
#include "point.hpp"

template <typename Type>
using vector = std::vector<Type>;

class BaseModel {
public:
    virtual void transform(BaseTransformator &) = 0;
};

class FrameModel: public BaseModel {
    vector<Point> points;
    vector<Link> links;
public:
    FrameModel();
    virtual void transform(BaseTransformator &) override;
};
