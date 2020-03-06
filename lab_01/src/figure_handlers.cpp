#include "../include/figure_handlers.h"

static err_t transform_figure(parr_t &points, const double conversion_matrix[4][4])
{
    double tmp[4];
    for (unsigned int i = 0; i < points.size; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j] = 0;
            tmp[j] += points.arr[i].x * conversion_matrix[0][j] +
                points.arr[i].y * conversion_matrix[1][j] + 
                points.arr[i].z * conversion_matrix[2][j] +
                points.arr[i].w * conversion_matrix[3][j];
        } 
        points.arr[i].x = tmp[0];
        points.arr[i].y = tmp[1];
        points.arr[i].z = tmp[2];
        points.arr[i].w = tmp[3];
    }

    return OK;
}


err_t move_figure(parr_t &points, const point_t &dp) // dp - delta point.
{
    double conversion_matrix[4][4] = { { 1., 0., 0., 0. },
                                       { 0., 1., 0., 0. },
                                       { 0., 0., 1., 0. },
                                       { dp.x, dp.y, dp.z, 1. } };
    return transform_figure(points, conversion_matrix);
}


err_t scale_figure(parr_t &points, const double sf) // sf - scale factor.
{
    if (sf == 0)
        return DATA_ERROR;

    point_t dcp = { .x = -points.cp.x, .y = -points.cp.y, .z = -points.cp.z, .w = 1 };
    err_t rc = OK;

    if ((rc = move_figure(points, dcp)))
        return rc;

    double conversion_matrix[4][4] = { { sf, 0., 0., 0. },
                                       { 0., sf, 0., 0. },
                                       { 0., 0., sf, 0. },
                                       { 0., 0., 0., 1. } };

    if ((rc = transform_figure(points, conversion_matrix)))
        return rc;

    point_t rdcp = { .x = points.cp.x, .y = points.cp.y, .z = points.cp.z, .w = 1 };
    if ((rc = move_figure(points, rdcp)))
        return rc;

    return OK;
}


err_t rotate_figure(parr_t &points, const point_t &ap)
{
    err_t rc = OK;

    point_t dcp = { .x = -points.cp.x, .y = -points.cp.y, .z = -points.cp.z, .w = 1 };
    if ((rc = move_figure(points, dcp)))
        return rc;

    if (fabs(ap.x) > std::numeric_limits<double>::epsilon())
    {
        double conversion_matrix[4][4] = { { 1., 0., 0., 0. },
                                           { 0., cos(ap.x), sin(ap.x), 0. },
                                           { 0., -sin(ap.x), cos(ap.x), 0. },
                                           { 0., 0., 0., 1. } };
        if ((rc = transform_figure(points, conversion_matrix)))
            return rc;
    }

    else if (fabs(ap.y) > std::numeric_limits<double>::epsilon())
    {
        double conversion_matrix[4][4] = { { cos(ap.y), 0., -sin(ap.y), 0. },
                                           { 0., 1., 0., 0. },
                                           { sin(ap.y), 0., cos(ap.y), 0. },
                                           { 0., 0., 0., 1. } };
        if ((rc = transform_figure(points, conversion_matrix)))
            return rc;
    }

    else if (fabs(ap.z) > std::numeric_limits<double>::epsilon())
    {
        double conversion_matrix[4][4] = { { cos(ap.z), sin(ap.z), 0., 0. },
                                           { -sin(ap.z), cos(ap.z), 0., 0. },
                                           { 0., 0., 1., 0. },
                                           { 0., 0., 0., 1. } };
        if ((rc = transform_figure(points, conversion_matrix)))
            return rc;
    }

    point_t rdcp = { .x = points.cp.x, .y = points.cp.y, .z = points.cp.z, .w = 1 };
    if ((rc = move_figure(points, rdcp)))
        return rc;

    return OK;
}
