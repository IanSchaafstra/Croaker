#include "log.h"
#include "../structs/env_data.h"

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "../structs/sprites.h"
#include "../util/colors.h"
#include "../util/time_utils.h"

log* log_init_from_config(const logconfig* conf) {
    log* l = malloc(sizeof(log));

    // l->start_time = l->diff_time = (double) clock() / CLOCKS_PER_SEC;
    l->posy = conf->row;
    l->posx = conf->col;
    clock_gettime(CLOCK_MONOTONIC, &l->s_time);
    clock_gettime(CLOCK_MONOTONIC, &l->d_time);

    l->dir = conf->dir;

    l->cooldown = conf->cooldown;

    l->collider.posx = l->prevposx = l->posx;
    l->collider.posy = l->prevposy = l->posy;
    l->collider.sizex = LOG_SIZE_X - 1;
    l->collider.sizey = LOG_SIZE_Y - 1;
    return l;
}

void log_update(log* log, const env_data* data) {
    clock_gettime(CLOCK_MONOTONIC, &log->d_time);
    log->prevposx = log->posx;
    log->prevposy = log->posy;

    long diff_ms = timespec_get_ms_difference(&log->s_time, &log->d_time);
    while (diff_ms >= log->cooldown) {
        diff_ms = timespec_get_ms_difference(&log->s_time, &log->d_time);
        timespec_add_ms(&log->s_time, log->cooldown);

        if (log->dir == RIGHT) {
            if (log->posx < data->cols) {
                log->posx++;
            } else {
                log->posx = -LOG_SIZE_X;
            }
        } else {
            if (log->posx > -LOG_SIZE_X) {
                log->posx--;
            } else {
                log->posx = data->cols;
            }
        }
    }

    log_update_aabb(log);
}

void log_draw(log* log, const env_data* data) {
    // clearing the previous position isn't necessary, considering
    // the water already gets drawn before the log does
    log_sprite_draw(log, data);
}

void log_update_aabb(log* log) {
    log->collider.posx = log->posx;
    log->collider.posy = log->posy;
}

void log_sprite_draw(log* log, const env_data* data) {
    int sprite[LOG_SIZE_Y][LOG_SIZE_X] = SPRITE_LOG;
    int x = log->posx;
    int y = log->posy;
    move(y, x);

    for (int row = 0; row < LOG_SIZE_Y; row++) {
        for (int col = 0; col < LOG_SIZE_X; col++) {
            move(row + y, col + x);
            if (!(row + y < 0 || col + x < 0 || row + y >= data->rows || col + x >= data->cols)) {
                switch (sprite[row][col]) {
                    case COLOR_BROWN:
                        attron(COLOR_PAIR(LOG_BROWN_COLOR));
                        break;
                    case COLOR_BEIGE:
                        attron(COLOR_PAIR(LOG_BEIGE_COLOR));
                        break;
                    default:
                        attron(COLOR_PAIR(WATER_COLOR));
                        break;
                }
                addch(' ');
            }
        }
    }
    attroff(COLOR_PAIR(DEFAULT_COLOR));
}