#include "../include/transform_figure.h"

err_t move_figure(parr_t &points, const transform_t &dp) // dp - delta point.
{
    err_t rc = OK;
    if (!points.arr || points.size <= 0)
        rc = DATA_ERROR;

    if (!rc)
    {
        for (unsigned int i = 0; i < points.size; i++)
            move_point(points.arr[i], dp);
        move_point(points.cp, dp);
    }

    return rc;
}


err_t scale_figure(parr_t &points, const double sf) // sf - scale factor.
{
    err_t rc = OK;
    if (!points.arr || points.size <= 0 ||
            fabs(sf) < DBL_EPSILON)
        rc = DATA_ERROR;

    if (!rc)
    {
        point_t &center = points.cp;
        for (unsigned int i = 0; i < points.size && !rc; i++)
            rc = scale_point(points.arr[i], sf, center);
    }

    return rc;
}


err_t rotate_figure(parr_t &points, const transform_t &ap)
{
    err_t rc = OK;
    if (!points.arr || points.size <= 0)
        rc = DATA_ERROR;

    if (!rc)
    {
        point_t &center = points.cp;

        for (unsigned int i = 0; i < points.size; i++)
            rotate_point(points.arr[i], ap, center);
    }

    return rc;
}

