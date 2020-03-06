#include "../include/command_handlers.h"

err_t move_command(figure_t &main_figure, const char code, const double &value)
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

    point_t dp = { .x = dx, .y = dy, .z = dz, .w = 1 };
    if (move_figure(main_figure.points, dp))
        return MOVE_ERROR;

    return OK;
}


err_t rotate_command(figure_t &main_figure, const char code, const double &value)
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

    point_t ap = { .x = ax, .y = ay, .z = az, .w = 1 };

    if (rotate_figure(main_figure.points, ap))
        return ROTATE_ERROR;
    return OK;
}

err_t scale_command(figure_t &main_figure, const char code, const double &value)
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
