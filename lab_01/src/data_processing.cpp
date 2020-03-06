#include "../include/data_processing.h"
#include "../include/computation.h"

using namespace std;

static figure_t main_figure = {};


void destroy_parr()
{
    if (main_figure.points.arr != NULL)
    {
        for (unsigned int i = 0; i < main_figure.points.size; i++)
            if (main_figure.points.arr[i] != NULL)
                free(main_figure.points.arr[i]);
        free(main_figure.points.arr);
    }

    if (main_figure.links.arr != NULL)
    {
        for (unsigned int i = 0; i < main_figure.links.size; i++)
            if (main_figure.links.arr[i] != NULL)
                free(main_figure.links.arr[i]);
        free(main_figure.links.arr);
    }
}


static err_t read_points(FILE *const f, parr_t &points_array)
{
    for (unsigned int i = 0; i < points_array.size; i++)
    {
        points_array.arr[i] = static_cast<double *>(calloc(4, sizeof(double)));
        if (!points_array.arr[i])
            return ALLOCATION_ERROR;

        if (fscanf(f, "%lf%lf%lf", &points_array.arr[i][0], &points_array.arr[i][1],
                    &points_array.arr[i][2]) != 3 * READED)
            return READ_ERROR;
        points_array.arr[i][3] = 1;
    }

    return OK;
}


static err_t add_link(larr_t &links_array, const unsigned int *const buffer,
        const unsigned int buf_size)
{
    unsigned int **tmp = static_cast<unsigned int **>(realloc(links_array.arr,
            sizeof(unsigned int *) * (links_array.size + 1)));
    if (!tmp)
        return ALLOCATION_ERROR;
    links_array.arr = tmp;

    links_array.arr[links_array.size] = static_cast<unsigned int *>(calloc(buf_size,
            sizeof(unsigned int)));
    if (!links_array.arr[links_array.size])
        return ALLOCATION_ERROR;

    for (unsigned int i = 0; i < buf_size; i++)
        links_array.arr[links_array.size][i] = buffer[i];
    return OK;
}

static err_t read_links(FILE *const f, larr_t &links_array, const unsigned int max_index)
{
    unsigned int buf[2];
    while (fscanf(f, "%u%u", buf, buf + 1) != 2 * READED) 
    {
        if (buf[0] > max_index || buf[1] > max_index)
            return DATA_ERROR;
        if (add_link(links_array, buf, 2))
            return ALLOCATION_ERROR;
    }
    return OK;
}


err_t read_from_file(const char *const filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return FILE_ERROR;

    if (fscanf(f, "%u", &main_figure.points.size) != READED)
        return READ_ERROR;

    main_figure.points.arr = static_cast<double **>(calloc(main_figure.points.size,
                                                           sizeof(double *)));
    if (!main_figure.points.arr)
        goto error_with_alloc;
    
    if (read_points(f, main_figure.points))
        goto error_with_alloc;

    if (read_links(f, main_figure.links, main_figure.points.size - 1))
        goto error_with_alloc;

    fclose(f);
    return OK;

error_with_alloc:
    destroy_parr();
    return ALLOCATION_ERROR;
}


err_t move_command(const char code, const double &value)
{
    double dx = 0, dy = 0, dz = 0;
    switch (code)
    {
        case MOVE_UP:
            dy = -value;
            break;
        case MOVE_DOWN:
            dy = value;
            break;
        case MOVE_RIGHT:
            dx = value;
            break;
        case MOVE_LEFT:
            dx = -value;
            break;
        case MOVE_BACK:
            dz = -value;
            break;
        case MOVE_FRONT:
            dz = value;
            break;
        default:
            return DATA_ERROR;
    }

    if (move_figure(main_figure.points, dx, dy, dz))
        return MOVE_ERROR;
    return OK;
}


err_t rotate_command(const char code, const double &value)
{
    double ax = 0, ay = 0, az = 0;
    switch (code)
    {
        case ROTATE_UP:
            ax = value / 180 * M_PI;
            break;
        case ROTATE_DOWN:
            ax = -value / 180 * M_PI;
            break;
        case ROTATE_RIGHT:
            ay = -value / 180 * M_PI;
            break;
        case ROTATE_LEFT:
            ay = value / 180 * M_PI;
            break;
        case ROTATE_RIGHTUP:
            az = value / 180 * M_PI;
            break;
        case ROTATE_LEFTUP:
            az = -value / 180 * M_PI;
            break;
    }

    if (rotate_figure(main_figure.points, ax, ay, az))
        return ROTATE_ERROR;
    return OK;
}



err_t scale_command(const char code, const double &value)
{
    if (value == 0)
        return DATA_ERROR;

    double scale_factor = 0;
    switch (code)
    {
        case SCALE_PLUS:
            scale_factor = value;
            break;
        case SCALE_MINUS:
            scale_factor = 1 / value;
            break;
    }

    if (scale_figure(main_figure.points, scale_factor))
        return SCALE_ERROR;
    return OK;
}
