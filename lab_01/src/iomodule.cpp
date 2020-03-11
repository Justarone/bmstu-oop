#include "../include/iomodule.h"

using namespace std;


// find center of figure.
static err_t find_center(parr_t &points)
{
    point_t &center = points.cp;
    center = init_point(0, 0, 0, 0);

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
    center.w = 1;
    return OK;
}


static void destroy_points(parr_t &points)
{
    if (points.arr != NULL)
    {
        free(points.arr);
        points.arr = NULL;
    }
}

static void destroy_links(larr_t &links)
{
    if (links.arr != NULL)
    {
        free(links.arr);
        links.arr = NULL;
    }
}

static void destroy_ppoints(pparr_t &points)
{
    if (points.arr != NULL)
    {
        free(points.arr);
        points.arr = NULL;
    }
}


void destroy_figure(figure_t &main_figure)
{
    destroy_points(main_figure.points);
    destroy_links(main_figure.links);
}


void destroy_projection(fpr_t &projection)
{
    destroy_ppoints(projection.points);
}


static err_t read_points(FILE *const f, parr_t &points_array)
{
    for (unsigned int i = 0; i < points_array.size; i++)
    {
        if (fscanf(f, "%lf%lf%lf", &points_array.arr[i].x, &points_array.arr[i].y,
                    &points_array.arr[i].z) != 3 * READED)
            return READ_ERROR;
        points_array.arr[i].w = 1;
    }

    return OK;
}


static err_t add_link(larr_t &links_array, const unsigned int l1, const unsigned int l2)
{
    link_t *tmp = static_cast<link_t *>(realloc(links_array.arr,
            sizeof(link_t) * (links_array.size + 1)));
    if (!tmp)
        return ALLOCATION_ERROR;
    links_array.arr = tmp;

    links_array.arr[links_array.size].l1 = l1;
    links_array.arr[links_array.size].l2 = l2;
    
    links_array.size++;
    return OK;
}


static err_t read_links(FILE *const f, larr_t &links_array, const unsigned int max_index)
{
    unsigned int l1, l2;
    while (fscanf(f, "%u%u", &l1, &l2) == 2 * READED) 
    {
        if (l1 > max_index || l2 > max_index)
            return DATA_ERROR;
        if (add_link(links_array, l1, l2))
            return ALLOCATION_ERROR;
    }
    return OK;
}


err_t read_from_file(figure_t &main_figure, const char *const filename)
{
    err_t rc = OK;
    FILE *f = fopen(filename, "r");

    if (!f)
        return FILE_ERROR;

    parr_t &points = main_figure.points;
    larr_t &links = main_figure.links;

    if (fscanf(f, "%u", &points.size) != READED)
        return READ_ERROR;

    points.arr = static_cast<point_t *>(calloc(points.size, sizeof(point_t)));
    if (!points.arr)
    {
        goto error_with_alloc;
        rc = ALLOCATION_ERROR;
    }
    
    if ((rc = read_points(f, points)))
        goto error_with_alloc;

    if ((rc = find_center(points)))
        goto error_with_alloc;

    if ((rc = read_links(f, links, points.size - 1)))
        goto error_with_alloc;

    fclose(f);
    return rc;

error_with_alloc:
    destroy_figure(main_figure);
    return rc;
}

