#pragma once

#include "link.hpp"
#include "point.hpp"
#include "vector.hpp"
//#include <vector>

template <typename Type>
using vector = Vector<Type>;
//using vector = std::vector<Type>;

class BaseModel {
public:
    virtual void transform(BaseTransformator &) = 0;
    virtual shared_ptr<BaseModel> clone() = 0;
};

class FrameModel: public BaseModel {
    vector<Point> _points;
    vector<Link> _links;
public:
    FrameModel() = default;
    FrameModel(FrameModel &);
    vector<Point> &getPoints();
    vector<Link> &getLinks();
    virtual void transform(BaseTransformator &) override;
    virtual shared_ptr<BaseModel> clone() override;
};
