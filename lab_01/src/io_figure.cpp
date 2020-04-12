#include "../include/io_figure.h"


static err_t read_from_file(figure_t &tmp_figure, FILE *const f);


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
    FILE *f = fopen(filename, "r");
    if (!f)
        return FILE_ERROR;
    
    figure_t tmp_figure = init_figure();
    err_t rc = read_from_file(tmp_figure, f);
    fclose(f);

    if (!rc)
    {
        destroy_figure(main_figure);
        main_figure = tmp_figure;
    }

    return rc;
}

static err_t read_from_file(figure_t &tmp_figure, FILE *const f)
{
    parr_t &points = tmp_figure.points;
    larr_t &links = tmp_figure.links;

    err_t rc = OK;

    if ((rc = get_points(points, f)))
        ;

    else if ((rc = get_links(links, f, points.size - 1)))
        destroy_points(points);

    else if ((rc = find_center(points)))
        destroy_figure(tmp_figure);

    return rc;
}

