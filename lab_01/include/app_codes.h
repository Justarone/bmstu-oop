#ifndef _APP_CODES_H_
#define _APP_CODES_H_

// Command codes.
enum { MOVE = 0, SCALE, ROTATE };

// Number of commands (move, scale, rotate).
#define CMD_N 3

// Move codes.
enum { MOVE_UP = 0, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT, MOVE_FRONT, MOVE_BACK };

// Scale codes.
enum { SCALE_PLUS = 0, SCALE_MINUS };

// Rotate codes.
enum { ROTATE_UP = 0, ROTATE_DOWN, ROTATE_LEFT, ROTATE_RIGHT, ROTATE_RIGHTUP, ROTATE_LEFTUP };

#endif
