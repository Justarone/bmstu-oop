#include "../include/figure_handlers.h"

static err_t transform_figure(parr_t &points, const double conversion_matrix[4][4])
{
    double tmp[4];
    point_t *const &points_array = points.arr;
    for (unsigned int i = 0; i < points.size; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tmp[j] = 0;
            tmp[j] += points_array[i].x * conversion_matrix[0][j] +
                points_array[i].y * conversion_matrix[1][j] + 
                points_array[i].z * conversion_matrix[2][j] +
                points_array[i].w * conversion_matrix[3][j];
        } 
        points_array[i].x = tmp[0];
        points_array[i].y = tmp[1];
        points_array[i].z = tmp[2];
        points_array[i].w = tmp[3];
    }

    return OK;
}


static err_t point_to_proj(ppoint_t &projection, const point_t &point)
{
    err_t rc = OK;
    projection.x = point.x;
    projection.y = point.y;
    return rc;
}


err_t move_figure(parr_t &points, const point_t &dp) // dp - delta point.
{
    double conversion_matrix[4][4] = { { 1., 0., 0., 0. },
                                       { 0., 1., 0., 0. },
                                       { 0., 0., 1., 0. },
                                       { dp.x, dp.y, dp.z, 1. } };

    err_t rc = OK;
    if ((rc = transform_figure(points, conversion_matrix)))
        return rc;

    point_t &center = points.cp;
    center.x += dp.x;
    center.y += dp.y;
    center.z += dp.z;

    return OK;
}


err_t scale_figure(parr_t &points, const double sf) // sf - scale factor.
{
    if (sf == 0)
        return DATA_ERROR;

    point_t center = points.cp;
    point_t dcp = init_point(-center.x, -center.y, -center.z, 1);
    point_t rdcp = init_point(center.x, center.y, center.z, 1);
    err_t rc = OK;

    if ((rc = move_figure(points, dcp)))
        return rc;

    double conversion_matrix[4][4] = { { sf, 0., 0., 0. },
                                       { 0., sf, 0., 0. },
                                       { 0., 0., sf, 0. },
                                       { 0., 0., 0., 1. } };

    if ((rc = transform_figure(points, conversion_matrix)))
        return rc;

    if ((rc = move_figure(points, rdcp)))
        return rc;

    return OK;
}


err_t rotate_figure(parr_t &points, const point_t &ap)
{
    err_t rc = OK;

    point_t center = points.cp;
    point_t dcp = init_point(-center.x, -center.y, -center.z, 1);
    point_t rdcp = init_point(center.x, center.y, center.z, 1);

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

    if ((rc = move_figure(points, rdcp)))
        return rc;

    return OK;
}


static err_t match_points(pparr_t &prj_points, const parr_t &fgr_points)
{
    if (prj_points.size != fgr_points.size)
    {
        ppoint_t *tmp = static_cast<ppoint_t *>(realloc(prj_points.arr,
                                                     sizeof(point_t) * fgr_points.size));
        if (!tmp)
            return ALLOCATION_ERROR;

        prj_points.arr = tmp;
        prj_points.size = fgr_points.size;
    }
    return OK;
}


err_t match_figure_project(fpr_t &figure_projection, const figure_t &main_figure)
{
    figure_projection.links = main_figure.links;

    err_t rc = OK;
    rc = match_points(figure_projection.points, main_figure.points);
    return rc;
}


err_t read_projection(pparr_t &prj_points, const parr_t &main_points)
{
    err_t rc = OK;

    for (unsigned int i = 0; i < main_points.size; i++)
    {
        if ((rc = point_to_proj(prj_points.arr[i], main_points.arr[i])))
            return rc;
    }
    return rc;
}
