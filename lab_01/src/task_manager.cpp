#include "../include/task_manager.h"

static figure_t main_figure = {};

const figure_t &get_figure()
{
    return main_figure;
}

err_t task_manager(const event_t &event, const double *value)
{
    static bool data_loaded = false;
    if (!data_loaded)
    {
        read_from_file(main_figure, POINTS_FILE);
        data_loaded = true;
    }
    switch (event.command)
    {
        case MOVE:
            if (move_command(main_figure, event.code, value[MOVE]))
                return MOVE_ERROR;
            break;

        case SCALE:
            if (scale_command(main_figure, event.code, value[SCALE]))
                return SCALE_ERROR;
            break;

        case ROTATE:
            if (rotate_command(main_figure, event.code, value[ROTATE]))
                return ROTATE_ERROR;
            break;

        default:
            // Error state.
            return STATE_ERROR;
    }
    return OK;
}

