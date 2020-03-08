#ifndef _DRAW_FUNCTION_H_
#define _DRAW_FUNCTION_H_

#include <gtkmm.h>
#include "structs.h"
#include "constants.h"

err_t draw_figure(Gtk::DrawingArea *da, const figure_t &figure);

#endif
