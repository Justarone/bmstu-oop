#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define FILENAME "meta/viewer.glade"
#define POINTS_FILE "meta/points.txt"

#define READED 1
typedef enum { OK = 0, FILE_ERROR, ALLOCATION_ERROR, READ_ERROR, DATA_ERROR, MOVE_ERROR,
               ROTATE_ERROR, SCALE_ERROR, COMMAND_ERROR } err_t;

#endif
