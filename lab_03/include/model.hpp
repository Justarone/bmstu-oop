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
    vector<Point> _points;
    vector<Link> _links;
public:
    FrameModel() = default;
    vector<Point> &getPoints();
    vector<Link> &getLinks();
    virtual void transform(BaseTransformator &) override;
};
