#ifndef _APP_CODES_H_
#define _APP_CODES_H_

// Number of conversion commands (move, scale, rotate).
#define CMD_N 3
// Conversion command codes (conversion commands).
enum { MOVE = 0, SCALE, ROTATE };

// Move codes.
enum { MOVE_UP = 0, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT, MOVE_FRONT, MOVE_BACK };
// Scale codes.
enum { SCALE_PLUS = 0, SCALE_MINUS };
// Rotate codes.
enum { ROTATE_UP = 0, ROTATE_DOWN, ROTATE_LEFT, ROTATE_RIGHT, ROTATE_RIGHTUP, ROTATE_LEFTUP };


// Non-conversion commands (first index one value bigger than last elem's in command codes enum).
enum { LOAD_DATA = ROTATE + 1, UPDATE_PROJECTION, DRAW, QUIT };
#define NO_CODE 0

#endif
