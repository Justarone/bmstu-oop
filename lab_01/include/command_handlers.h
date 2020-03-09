#ifndef _COMMAND_HANDLERS_H_
#define _COMMAND_HANDLERS_H_

#include "app_codes.h"
#include "constants.h"
#include "figure_handlers.h"

err_t move_command(figure_t &main_figure, const char code, const double &value);
err_t rotate_command(figure_t &main_figure, const char code, const double &value);
err_t scale_command(figure_t &main_figure, const char code, const double &value);
err_t get_projection(fpr_t &figure_projection, const figure_t &main_figure);

#endif
