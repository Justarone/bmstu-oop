#ifndef _POINTS_ARR_H_
#define _POINTS_ARR_H_

#include "points.h"
#include <cstdlib>
#include <gtkmm.h>

struct points_array
{
    point_t *arr;
    unsigned int size;
    point_t cp;
};
using parr_t = struct points_array;

struct projection_points_array
{
    ppoint_t *arr;
    unsigned int size;
};
using pparr_t = struct projection_points_array;

#endif
