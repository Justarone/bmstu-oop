#include "../include/iomodule.h"

using namespace std;


// find center of figure.
static err_t find_center(parr_t &points)
{
    points.cp.x = 0;
    points.cp.y = 0;
    points.cp.z = 0;
    points.cp.w = 0;

    if (points.size <= 0)
        return DATA_ERROR;

    for (unsigned int i = 0; i < points.size; i++)
    {
        points.cp.x += points.arr[i].x;
        points.cp.y += points.arr[i].y;
        points.cp.z += points.arr[i].z;
    }

    points.cp.x /= points.size;
    points.cp.y /= points.size;
    points.cp.z /= points.size;
    points.cp.w = 1;
    return OK;
}


void destroy_figure(figure_t &main_figure)
{
    if (main_figure.points.arr != NULL)
    {
        free(main_figure.points.arr);
        main_figure.points.arr = NULL;
    }

    if (main_figure.links.arr != NULL)
    {
        free(main_figure.links.arr);
        main_figure.links.arr = NULL;
    }
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

    if (fscanf(f, "%u", &main_figure.points.size) != READED)
        return READ_ERROR;

    main_figure.points.arr = static_cast<point_t *>(calloc(main_figure.points.size,
                                                           sizeof(point_t)));
    if (!main_figure.points.arr)
    {
        goto error_with_alloc;
        rc = ALLOCATION_ERROR;
    }
    
    if ((rc = read_points(f, main_figure.points)))
        goto error_with_alloc;

    if ((rc = find_center(main_figure.points)))
        goto error_with_alloc;

    if ((rc = read_links(f, main_figure.links, main_figure.points.size - 1)))
        goto error_with_alloc;

    fclose(f);
    return rc;

error_with_alloc:
    destroy_figure(main_figure);
    return rc;
}

