#include "../include/transform_point.h"
#include <cstdio>

err_t move_point(point_t &point, const transform_t &dp)
{
    point.x += dp.x;
    point.y += dp.y;
    point.z += dp.z;
    return OK;
}


err_t scale_point(point_t &point, const double sf, const point_t &cp)
{
    if (fabs(sf) < std::numeric_limits<double>::epsilon())
        return DATA_ERROR;

    point.x = ((point.x - cp.x) * sf) + cp.x;
    point.y = ((point.y - cp.y) * sf) + cp.y;
    point.z = ((point.z - cp.z) * sf) + cp.z;

    return OK;
}


err_t rotate_point(point_t &point, const transform_t &ap, const point_t &cp)
{
    int rotate_flag = static_cast<int>(fabs(ap.x) > 
                                       std::numeric_limits<double>::epsilon());
    rotate_flag += static_cast<int>(fabs(ap.y) >
                                    std::numeric_limits<double>::epsilon());
    rotate_flag += static_cast<int>(fabs(ap.z) >
                                    std::numeric_limits<double>::epsilon());
    if (rotate_flag >= 2)
        return DATA_ERROR;

    point_t tmp = init_point();

    if (fabs(ap.x) > std::numeric_limits<double>::epsilon())
    {
        tmp.x = point.x;
        tmp.y = ((point.y - cp.y) * cos(ap.x) - (point.z - cp.z) * sin(ap.x)) + cp.y;
        tmp.z = ((point.y - cp.y) * sin(ap.x) + (point.z - cp.z) * cos(ap.x)) + cp.z;
    }
    else if (fabs(ap.y) > std::numeric_limits<double>::epsilon())
    {
        tmp.y = point.y;
        tmp.x = ((point.x - cp.x) * cos(ap.y) + (point.z - cp.z) * sin(ap.y)) + cp.x;
        tmp.z = (-(point.x - cp.x) * sin(ap.y) + (point.z - cp.z) * cos(ap.y)) + cp.z;

    }
    else if (fabs(ap.z) > std::numeric_limits<double>::epsilon())
    {
        tmp.z = point.z;
        tmp.x = ((point.x - cp.x) * cos(ap.z) - (point.y - cp.y) * sin(ap.z)) + cp.x;
        tmp.y = ((point.x - cp.x) * sin(ap.z) + (point.y - cp.y) * cos(ap.z)) + cp.y;
    }

    point = tmp;
    return OK;
}


transform_t init_transform(const double x, const double y, const double z)
{
    transform_t transformation;
    transformation.x = x;
    transformation.y = y;
    transformation.z = z;

    return transformation;
}
