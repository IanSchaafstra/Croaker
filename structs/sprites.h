#pragma once

#include <ncurses.h>

#include "config.h"

// const int R = COLOR_RED;
// const int G = COLOR_GREY;
#define R COLOR_RED
#define G COLOR_GREY
#define B COLOR_BLUE
#define BR COLOR_BROWN
#define BE COLOR_BEIGE
#define N 0

#define SPRITE_CAR_1 {N, N, B, B, R, R, R, R, R, R, R, N}
#define SPRITE_CAR_2 {B, B, B, B, R, R, R, R, R, R, R, R}
#define SPRITE_CAR_3 {R, R, G, G, R, R, R, R, R, G, G, R}
#define SPRITE_CAR {SPRITE_CAR_1, SPRITE_CAR_2, SPRITE_CAR_3}

#define SPRITE_LOG_1 {N, BE, BR, BR, BR, BR, BR, BR, BR, BR, BR, N}
#define SPRITE_LOG_2 {BE, BE, BE, BR, BR, BR, BR, BR, BR, BR, BR, BR}
#define SPRITE_LOG_3 {N, BE, BR, BR, BR, BR, BR, BR, BR, BR, BR, N}
#define SPRITE_LOG {SPRITE_LOG_1, SPRITE_LOG_2, SPRITE_LOG_3}
