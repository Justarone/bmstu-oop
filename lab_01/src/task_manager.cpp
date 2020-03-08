#include "../include/task_manager.h"


err_t task_manager(const event_t &event)
{
    err_t rc = OK;
    static figure_t main_figure = { { NULL, 0 }, { NULL, 0 } };

    switch (event.command)
    {
        case LOAD_DATA:
            rc = read_from_file(main_figure, POINTS_FILE);
            break;
        case MOVE:
            rc = move_command(main_figure, event.code, event.data.value[MOVE]);
            break;
        case SCALE:
            rc = scale_command(main_figure, event.code, event.data.value[SCALE]);
            break;
        case ROTATE:
            rc = rotate_command(main_figure, event.code, event.data.value[ROTATE]);
            break;
        case DRAW:
            rc = draw_figure(event.data.area, main_figure);
            break;
        case QUIT:
            destroy_figure(main_figure);
            break;
        default:
            rc = COMMAND_ERROR;
    }
    return rc;
}

