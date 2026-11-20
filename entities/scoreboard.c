#include "scoreboard.h"

#include <ncurses.h>
#include <stdlib.h>

#include "../util/colors.h"
#include "../util/int_utils.h"

scoreboard* scoreboard_init(const env_data* data) {
    scoreboard* board = malloc(sizeof(scoreboard));

    board->score = 0;
    for (int i = 0; i < 4; i++) {
        board->score_str[i] = 0;
    }

    board->posx = data->cols - 4;
    board->posy = 2;
    board->pos_mark = data->rows;

    return board;
}

void scoreboard_update(scoreboard* board, const env_data* data) {
    board->posx = data->cols - 4; // in case the window resizes

    scoreboard_update_score_str(board);
}

void scoreboard_draw(scoreboard* board, const env_data* data) {
    attron(COLOR_PAIR(DEFAULT_COLOR));
    move(board->posy, board->posx - 7);
    addstr("SCORE: ");
    move(board->posy, board->posx);
    for (int i = 0; i < 4; i++) {
        move(board->posy, board->posx + i);
        addch(board->score_str[i]);
    }

}

void scoreboard_update_score_str(scoreboard* board) {
    int index = 3;
    for (int i = 0; i < 4; i++) {
        int digit = get_nth_digit(board->score, i + 1);
        if (digit == -1) {
            board->score_str[index] = '0';
        } else {
            board->score_str[index] = digit + '0';
        }
        index--;
    }
}

void scoreboard_increase_score(scoreboard* board) {
    board->score++;
}

void scoreboard_update_pos_mark(scoreboard* board, int pos) {
    if (pos < board->pos_mark) {
        board->pos_mark = pos;
        scoreboard_increase_score(board);
    }
}