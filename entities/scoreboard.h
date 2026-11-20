#pragma once

#include "../structs/env_data.h"

struct scoreboard {
    int score;
    int posx, posy;
    char score_str[4];
    int pos_mark;
};
typedef struct scoreboard scoreboard;

scoreboard* scoreboard_init(const env_data* data);
void scoreboard_update(scoreboard* board, const env_data* data);
void scoreboard_update_score_str(scoreboard* board);
void scoreboard_draw(scoreboard* board, const env_data* data);
void scoreboard_increase_score(scoreboard* board);
void scoreboard_update_pos_mark(scoreboard* board, int pos);