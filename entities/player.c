#include "player.h"
#include "log.h"
#include "../structs/env_data.h"

#include <stdlib.h>
#include <ncurses.h>

#include "../structs/config.h"
#include "../util/colors.h"

player* player_init(const env_data* data) {
    player* p = malloc(sizeof(player));

    p->curr_lane = p->prev_lane = NONE;

    p->collider.posx = p->posx = data->cols / 2;
    p->start_lane = p->collider.posy = p->posy = (data->rows - data->rows % PLAYER_SIZE_Y) - PLAYER_SIZE_Y;
    p->collider.sizex = PLAYER_SIZE_X - 1;
    p->collider.sizey = PLAYER_SIZE_Y - 1;

    return p;
}

void player_update(player* player, const env_data* data) {
    player->prevposx = player->posx;
    player->prevposy = player->posy;

    if (player->on_log != NULL) {
        //if (player->on_log->prevposx != player->on_log->posx) {
            //if (player->on_log->dir == LEFT) {
                player->posx = player->on_log->posx + player->log_offset;
            // } else {
            //     player->posx++;
            // }
        // }
    }

    switch (player->input) {
        case KEY_UP:
            player->posy -= PLAYER_SIZE_Y;
            break;
        case KEY_DOWN:
            player->posy += PLAYER_SIZE_Y;
            break;
        case KEY_LEFT:
            player->posx -= PLAYER_SIZE_X;
            if (player->log_offset != 999) {
                player->log_offset -= PLAYER_SIZE_X;
            }
            break;
        case KEY_RIGHT:
            player->posx += PLAYER_SIZE_X;
            if (player->log_offset != 999) {
                player->log_offset += PLAYER_SIZE_X;
            }
            break;
        default:
            break;
    }
    if (player->posx < 1) {
        player->posx = 1;
    } else if (player->posx > data->cols - PLAYER_SIZE_X) {
        player->posx = data->cols - PLAYER_SIZE_X;
    }

    if (player->posy + PLAYER_SIZE_Y > data->rows - 1) {
        player->posy = data->rows - PLAYER_SIZE_Y - (data->rows % PLAYER_SIZE_Y);
    }

    if (player->posy < 0) {
        player->posy = 0;
    }

    player_update_aabb(player);
}

void player_draw(player* player) {
    if ((player->prevposx != player->posx || player->prevposy != player->posy) && player->posy - player->prevposy <= 3) {
        // move(player->prevposy, player->prevposx);
        // addch(' ');
        bool player_on_grass = player->prev_lane == GRASS; // && player->posy == player->prevposy;
        int lines_drawn = 0;
        for (int i = player->prevposy; i < player->prevposy + PLAYER_SIZE_Y; i++) {
            lines_drawn++;
            for (int j = player->prevposx; j < player->prevposx + PLAYER_SIZE_X; j++) {
                if (lines_drawn == 2 && ((j == player->prevposx) || (j == player->prevposx + PLAYER_SIZE_X - 1))) {
                    continue;
                }
                if (lines_drawn == 1 && (j > player->prevposx && j < player->prevposx + PLAYER_SIZE_X - 1)) {
                    continue;
                }
                if (player_on_grass) {
                    attron(COLOR_PAIR(GRASS_COLOR));
                }
                move(i, j);
                addch(' ');
                if (player_on_grass) {
                    attroff(COLOR_PAIR(GRASS_COLOR));
                }
            }
        }
    }
    int lines_drawn = 0;
    for (int i = player->posy; i < player->posy + PLAYER_SIZE_Y; i++) {
        lines_drawn++;
        for (int j = player->posx; j < player->posx + PLAYER_SIZE_X; j++) {
            // attron(COLOR_PAIR(FROG_COLOR));
            if (lines_drawn == 2 && ((j == player->posx) || (j == player->posx + PLAYER_SIZE_X - 1))) {
                attroff(COLOR_PAIR(FROG_COLOR));
                continue;
            } else if (lines_drawn == 1 && (j > player->posx && j < player->posx + PLAYER_SIZE_X - 1)) {
                attroff(COLOR_PAIR(FROG_COLOR));
                continue;
            } else {
                attron(COLOR_PAIR(FROG_COLOR));
            }
            move(i, j);
            // addstr("    ");
            addch(' ');
        }
        attroff(COLOR_PAIR(FROG_COLOR));
    }
    // move(player->posy, player->posx);
    // addch('&');
}

void player_update_aabb(player* player) {
    player->collider.posx = player->posx;
    player->collider.posy = player->posy;
}

void player_set_on_log(player* player, log* log) {
    if (player->on_log != log) { // check if the player jumped from one log to another
        player->log_offset = 999;
    }
    player->on_log = log;
    if (player->log_offset == 999) {
        player->log_offset = player->posx - log->posx;
    }
}

void player_clear_log(player* player) {
    player->on_log = NULL;
    player->log_offset = 999;
}

void player_set_input(player* player, int input) {
    player->input = input;
}