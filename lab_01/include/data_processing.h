#ifndef _DATA_PROCESSING_H_
#define _DATA_PROCESSING_H_

#include "../include/structs.h"
#include "../include/constants.h"
#include "../include/app_codes.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

err_t read_from_file(const char *const filename);
void destroy_parr();
err_t move_command(const char code, const double &value);
err_t rotate_command(const char code, const double &value);
err_t scale_command(const char code, const double &value);


#endif
