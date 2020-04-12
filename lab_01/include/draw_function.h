#ifndef _DRAW_FUNCTION_H_
#define _DRAW_FUNCTION_H_

#include <gtkmm-3.0/gtkmm.h>
#include "event_data.h"
#include "figure.h"
#include "constants.h"
#include "draw_module.h"

err_t draw_figure(draw_data_t &data, const fpr_t &figure);

#endif
