#include "../include/transform_figure.h"

err_t move_figure(parr_t &points, const point_t &dp) // dp - delta point.
{
    if (!points.arr || points.size <= 0)
        return DATA_ERROR;

    err_t rc = OK;

    for (unsigned int i = 0; i < points.size; i++)
        if ((rc = move_point(points.arr[i], dp)))
            return rc;

    rc = move_point(points.cp, dp);
    return rc;
}


err_t scale_figure(parr_t &points, const double sf) // sf - scale factor.
{
    if (!points.arr || points.size <= 0 ||
            fabs(sf) < std::numeric_limits<double>::epsilon())
        return DATA_ERROR;

    err_t rc = OK;
    point_t &center = points.cp;

    for (unsigned int i = 0; i < points.size; i++)
        if ((rc = scale_point(points.arr[i], sf, center)))
            return rc;

    return rc;
}


err_t rotate_figure(parr_t &points, const point_t &ap)
{
    if (!points.arr || points.size <= 0)
        return DATA_ERROR;

    err_t rc = OK;
    point_t &center = points.cp;

    for (unsigned int i = 0; i < points.size; i++)
        if ((rc = rotate_point(points.arr[i], ap, center)))
            return rc;

    return rc;
}

