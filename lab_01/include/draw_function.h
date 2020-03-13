#ifndef _DRAW_FUNCTION_H_
#define _DRAW_FUNCTION_H_

#include <gtkmm.h>
#include "figure.h"
#include "constants.h"

err_t draw_figure(Gtk::DrawingArea *da, const fpr_t &figure);

#endif
