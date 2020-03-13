#include "../include/io_figure.h"


void destroy_figure(figure_t &main_figure)
{
    destroy_points(main_figure.points);
    destroy_links(main_figure.links);
}


void destroy_projection(fpr_t &projection)
{
    destroy_ppoints(projection.points);
    destroy_links(projection.links);
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

    if (allocate_points(points))
    {
        rc = ALLOCATION_ERROR;
        destroy_figure(main_figure);
        return rc;
    }
    
    if ((rc = read_points(f, points)))
    {
        destroy_figure(main_figure);
        return rc;
    }

    if ((rc = find_center(points)))
    {
        destroy_figure(main_figure);
        return rc;
    }

    if ((rc = read_links(f, links, points.size - 1)))
    {
        destroy_figure(main_figure);
        return rc;
    }

    fclose(f);
    return rc;
}
