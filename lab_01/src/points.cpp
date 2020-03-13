#include "../include/points.h"


point_t init_point(const double x, const double y, const double z, const double w)
{
    point_t point;
    point.x = x;
    point.y = y;
    point.z = z;
    point.w = w;

    return point;
}

ppoint_t init_proj_point(const double x, const double y)
{
    ppoint_t point;
    point.x = x;
    point.y = y;
    return point;
}

