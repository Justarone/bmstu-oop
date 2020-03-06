#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

#include "constants.h"
#include "structs.h"
#include "app_codes.h"
#include "command_handlers.h"
#include "iomodule.h"

err_t task_manager(const event_t &event, const double *value);
const figure_t &get_figure();

#endif
