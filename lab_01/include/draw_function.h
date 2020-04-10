#ifndef _DRAW_FUNCTION_H_
#define _DRAW_FUNCTION_H_

#include <gtkmm-3.0/gtkmm.h>
#include "figure.h"
#include "constants.h"
#include "draw_module.h"

err_t draw_figure(Gtk::DrawingArea *const &da, const canvas_conf &conf, const fpr_t &figure);

#endif
