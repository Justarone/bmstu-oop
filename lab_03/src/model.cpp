#include "model.hpp"

vector<Link> &FrameModel::getLinks() {
    return _links;
}

vector<Point> &FrameModel::getPoints() {
    return _points;
}

void FrameModel::transform(BaseTransformator &transformator) {
    auto &points = getPoints();
    for (auto &point: points) {
        point = transformator.transform(point);
    }
}

FrameModel::FrameModel(FrameModel &inModel) {
    _points = inModel._points;
    _links = inModel._links;
}

shared_ptr<BaseModel> FrameModel::clone() {
    shared_ptr<BaseModel> model(new FrameModel(*this));
    return model;
}
