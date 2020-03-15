#include "../include/command_handlers.h"

err_t move_command(figure_t &main_figure, const char code, const trans_data_t &data)
{
    double value = data.value;
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

    point_t dp = init_point(dx, dy, dz, 1);
    err_t rc = move_figure(main_figure.points, dp);
    return rc;
}


err_t rotate_command(figure_t &main_figure, const char code, const trans_data_t &data)
{
    double value = data.value;
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
            ay = value / 180 * M_PI;
            break;
        case ROTATE_LEFT:
            ay = -value / 180 * M_PI;
            break;
        case ROTATE_RIGHTUP:
            az = -value / 180 * M_PI;
            break;
        case ROTATE_LEFTUP:
            az = value / 180 * M_PI;
            break;
    }

    point_t ap = init_point(ax, ay, az, 1);

    err_t rc = rotate_figure(main_figure.points, ap);
    return rc;
}

err_t scale_command(figure_t &main_figure, const char code, const trans_data_t &data)
{
    double value = data.value;
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

    err_t rc = scale_figure(main_figure.points, scale_factor);
    return rc;
}


err_t get_projection(prj_data_t &data, const figure_t &main_figure)
{
    if (!data.projection)
        return DATA_ERROR;
    fpr_t &figure_projection = *data.projection;

    err_t rc = match_figure_project(figure_projection, main_figure);
    if (rc)
        return rc;

    rc = read_projection(figure_projection.points, main_figure.points);
    return rc;
}


void destroy_all(figure_t &main_figure, prj_data_t &data)
{
    fpr_t *projection = data.projection; 
    destroy_figure(main_figure);
    if (projection)
        destroy_projection(*projection);
}

err_t read_from_file(figure_t &figure, load_data_t &data)
{
    const char *filename = data.filename;
    if (!filename)
        return DATA_ERROR;
    return read_from_file(figure, filename);
}

err_t draw_figure(draw_data_t &draw_data, const prj_data_t &prj_data)
{
    Gtk::DrawingArea * &area = draw_data.area;
    const fpr_t * projection = prj_data.projection;

    if (!area || !projection)
        return DATA_ERROR;
    err_t rc = draw_figure(area, *projection);
    return rc;        
}
