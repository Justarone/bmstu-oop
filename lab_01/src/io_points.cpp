#include "../include/io_points.h"

// find center of figure.
err_t find_center(parr_t &points)
{
    point_t &center = points.cp;
    center = init_point(0, 0, 0);

    if (points.size <= 0)
        return DATA_ERROR;

    const point_t *const &points_array = points.arr;
    for (unsigned int i = 0; i < points.size; i++)
    {
        center.x += points_array[i].x;
        center.y += points_array[i].y;
        center.z += points_array[i].z;
    }

    center.x /= points.size;
    center.y /= points.size;
    center.z /= points.size;

    return OK;
}


err_t allocate_points(parr_t &points)
{
    points.arr = static_cast<point_t *>(calloc(points.size, sizeof(point_t)));
    if (!points.arr)
        return ALLOCATION_ERROR;
    return OK;
}

err_t read_points(FILE *const f, parr_t &points_array)
{
    for (unsigned int i = 0; i < points_array.size; i++)
    {
        if (fscanf(f, "%lf%lf%lf", &points_array.arr[i].x, &points_array.arr[i].y,
                    &points_array.arr[i].z) != 3 * READED)
            return READ_ERROR;
    }

    return OK;
}


void destroy_points(parr_t &points)
{
    if (points.arr != NULL)
    {
        free(points.arr);
        points.arr = NULL;
    }
}


void destroy_ppoints(pparr_t &points)
{
    if (points.arr != NULL)
    {
        free(points.arr);
        points.arr = NULL;
    }
}

err_t get_points(parr_t &points, FILE *const f)
{
    err_t rc = OK;

    if (fscanf(f, "%u", &points.size) != READED)
        rc = READ_ERROR;

    else if ((rc = allocate_points(points)))
        ;

    else if ((rc = read_points(f, points)))
        destroy_points(points);

    return rc;
}
