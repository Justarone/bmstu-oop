#include "../include/command_handlers.h"

err_t move_command(figure_t &main_figure, const char code, const trans_data_t &data)
{
    double value = data.value;
    double dx = 0, dy = 0, dz = 0;

    dx += CHECK_CODE(code, MOVE_RIGHT) ? value : 0;
    dx += CHECK_CODE(code, MOVE_LEFT) ? -value : 0;

    dy += CHECK_CODE(code, MOVE_DOWN) ? value : 0;
    dy += CHECK_CODE(code, MOVE_UP) ? -value : 0;

    dz += CHECK_CODE(code, MOVE_FRONT) ? value : 0;
    dz += CHECK_CODE(code, MOVE_BACK) ? -value : 0;

    transform_t move_params = init_transform(dx, dy, dz);
    err_t rc = move_figure(main_figure.points, move_params);
    return rc;
}


err_t rotate_command(figure_t &main_figure, const char code, const trans_data_t &data)
{
    double value = data.value / 180 * M_PI;
    double ax = 0, ay = 0, az = 0;

    ax += CHECK_CODE(code, ROTATE_DOWN) ? -value : 0;
    ax += CHECK_CODE(code, ROTATE_UP) ? value : 0;

    ay += CHECK_CODE(code, ROTATE_LEFT) ? -value : 0;
    ay += CHECK_CODE(code, ROTATE_RIGHT) ? value : 0;

    az += CHECK_CODE(code, ROTATE_RIGHTUP) ? -value : 0;
    az += CHECK_CODE(code, ROTATE_LEFTUP) ? value : 0;

    transform_t rotate_params = init_transform(ax, ay, az);
    err_t rc = rotate_figure(main_figure.points, rotate_params);
    return rc;
}

err_t scale_command(figure_t &main_figure, const char code, const trans_data_t &data)
{
    double value = data.value;
    err_t rc = OK;

    if (value == 0)
        rc = DATA_ERROR;

    double scale_factor = 0;
    if (!rc)
    {
        if (code != SCALE_MINUS && code != SCALE_PLUS)
            rc = DATA_ERROR;
        else
            scale_factor = (code == SCALE_PLUS) ? value : 1 / value;
    }

    if (!rc)
        rc = scale_figure(main_figure.points, scale_factor);

    return rc;
}


err_t get_projection(prj_data_t &data, const figure_t &main_figure)
{
    if (!data.projection)
        return DATA_ERROR;

    fpr_t &figure_projection = *data.projection;
    fpr_t tmp_projection = init_projection();

    err_t rc = match_figure_project(tmp_projection, main_figure);
    if (!rc)
        rc = read_projection(tmp_projection.points, main_figure.points);
    if (!rc)
    {
        destroy_projection(figure_projection);
        figure_projection = tmp_projection;
    }
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
    if (!draw_data.area || !prj_data.projection)
        return DATA_ERROR;
    err_t rc = draw_figure(draw_data.area, draw_data.conf, *prj_data.projection);
    return rc;        
}
