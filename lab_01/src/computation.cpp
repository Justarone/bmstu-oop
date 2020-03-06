#include "../include/computation.h"
#include <limits>

// find center of figure.
static err_t find_center(const parr_t &points, double &x, double &y, double &z)
{
    x = (y = (z = 0));
    for (unsigned int i = 0; i < points.size; i++)
    {
        x += points.arr[i][0];
        y += points.arr[i][1];
        z += points.arr[i][2];
    }
    x /= points.size;
    y /= points.size;
    z /= points.size;

    return OK;
}

static err_t transform_figure(parr_t &points, const double conversion_matrix[4][4])
{
    double tmp[4];
    for (unsigned int i = 0; i < points.size; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j] = 0;
            for (int k = 0; k < 4; k++)
                tmp[j] += points.arr[i][k] * conversion_matrix[k][j];
        } 
        for (int j = 0; j < 4; j++)
            points.arr[i][j] = tmp[j];
    }

    return OK;
}

err_t move_figure(parr_t &points, const double dx, const double dy, const double dz)
{
    double conversion_matrix[4][4] = { { 1., 0., 0., 0. },
                                       { 0., 1., 0., 0. },
                                       { 0., 0., 1., 0. },
                                       { dx, dy, dz, 1. } };
    transform_figure(points, conversion_matrix);
    return OK;
}


err_t scale_figure(parr_t &points, const double sf) // sf - scale factor.
{
    if (sf == 0)
        return DATA_ERROR;

    double x = 0, y = 0, z = 0; // center coordinates.
    find_center(points, x, y, z);
    move_figure(points, -x, -y, -z); // move to the center for correct transformation.

    double conversion_matrix[4][4] = { { sf, 0., 0., 0. },
                                       { 0., sf, 0., 0. },
                                       { 0., 0., sf, 0. },
                                       { 0., 0., 0., 1. } };

    transform_figure(points, conversion_matrix); // move back from the center.

    move_figure(points, x, y, z);
    return OK;
}


err_t rotate_figure(parr_t &points, const double ax, const double ay, const double az)
{
    double x = 0, y = 0, z = 0; // center coordinates.
    find_center(points, x, y, z);
    move_figure(points, -x, -y, -z); // move to the center for correct transformation.

    if (abs(ax) > std::numeric_limits<double>::epsilon())
    {
        double conversion_matrix[4][4] = { { 1., 0., 0., 0. },
                                           { 0., cos(ax), sin(ax), 0. },
                                           { 0., -sin(ax), cos(ax), 0. },
                                           { 0., 0., 0., 1. } };
        transform_figure(points, conversion_matrix);
    }

    else if (abs(ay) > std::numeric_limits<double>::epsilon())
    {
        double conversion_matrix[4][4] = { { cos(ax), 0., -sin(ax), 0. },
                                           { 0., 1., 0., 0. },
                                           { sin(ax), 0., cos(ax), 0. },
                                           { 0., 0., 0., 1. } };
        transform_figure(points, conversion_matrix);
    }

    else if (abs(az) > std::numeric_limits<double>::epsilon())
    {
        double conversion_matrix[4][4] = { { cos(ax), sin(ax), 0., 0. },
                                           { -sin(ax), cos(ax), 0., 0. },
                                           { 0., 0., 1., 0. },
                                           { 0., 0., 0., 1. } };
        transform_figure(points, conversion_matrix);
    }

    move_figure(points, x, y, z);
    return OK;
}
