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
