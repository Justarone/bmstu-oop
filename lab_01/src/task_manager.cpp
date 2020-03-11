#include "../include/task_manager.h"


err_t task_manager(const event_t &event)
{
    err_t rc = OK;
    static figure_t main_figure = init_figure();
    const event_data_t &data = event.data;

    switch (event.command)
    {
        case LOAD_DATA:
            rc = read_from_file(main_figure, POINTS_FILE);
            break;
        case MOVE:
            rc = move_command(main_figure, event.code, data.value[MOVE]);
            break;
        case SCALE:
            rc = scale_command(main_figure, event.code, data.value[SCALE]);
            break;
        case ROTATE:
            rc = rotate_command(main_figure, event.code, data.value[ROTATE]);
            break;
        case UPDATE_PROJECTION:
            rc = get_projection(*data.projection, main_figure);
            break;
        case DRAW:
            rc = draw_figure(event.data.area, *data.projection);
            break;
        case QUIT:
            destroy_figure(main_figure);
            destroy_projection(*data.projection);
            break;
        default:
            rc = COMMAND_ERROR;
    }
    return rc;
}


event_t init_event(const char command, const char code, Gtk::DrawingArea *const area,
        double *const value, fpr_t *const projection)
{
    event_data_t data;
    data.area = area;
    data.value = value;

    event_t event;
    event.command = command;
    event.code = code;
    event.data = data;

    event.data.projection = projection;

    return event;
}

