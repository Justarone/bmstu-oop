#ifndef _TRANSFORM_POINT_H_
#define _TRANSFORM_POINT_H_

#include "points.h"
#include "constants.h"
#include <limits>
#include <cmath>

err_t move_point(point_t &point, const point_t &dp);
err_t scale_point(point_t &point, const double sf, const point_t &center);
err_t rotate_point(point_t &point, const point_t &ap, const point_t &center);

#endif
