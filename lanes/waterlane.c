#include "waterlane.h"

#include <ncurses.h>

#include "../structs/env_data.h"

#include <stdlib.h>

// #include "lanemanager.h"
#include "../util/colors.h"
#include "../entities/player.h"

waterlane* waterlane_init(const env_data* data, int row) {
    waterlane* lane = malloc(sizeof(waterlane));

    lane->row = row;
    int direction = rand() % 2;
    if (direction == 0) {
        lane->dir = RIGHT;
    } else {
        lane->dir = LEFT;
    }

    int max_entities;
    if ((LOG_SIZE_X + 15) * 2 > data->cols) { // for very narrow terminals
        max_entities = 2;
    } else {
        max_entities = (data->cols / (LOG_SIZE_X + 15));
    }

    double cooldown_offset = (rand() % 400 - 200);

    // lane->n_logs = rand() % 4 + 4;
    lane->n_logs = rand() % (max_entities) + (max_entities / 2);
    if (lane->n_logs > 16) {
        lane->n_logs = 16;
    }
    for (int i = 0; i < lane->n_logs; i++) {
        int offset = rand() % 12 + 2;
        int log_pos_x = data->cols / lane->n_logs * i + offset;
        logconfig conf;
        conf.col = log_pos_x;
        conf.row = row;
        conf.cooldown = LOG_COOLDOWN + cooldown_offset;
        conf.dir = lane->dir;
        log* l = log_init_from_config(&conf);
        lane->logs[i] = l;
    }

    return lane;
}

void waterlane_update(waterlane* lane, const env_data* data) {
    for (int i = 0; i < lane->n_logs; i++) {
        log_update(lane->logs[i], data);
    }
}

void waterlane_draw(waterlane* lane, const env_data* data) {
    attron(COLOR_PAIR(WATER_COLOR));
    for (int y = lane->row; y < lane->row + 3; y++) { // 3 is LANE_HEIGHT, but I don't use that because of circular imports
        for (int x = 0; x < data->cols; x++) {
            move(y, x);
            addch(' ');
        }
    }
    attroff(COLOR_PAIR(WATER_COLOR));
    for (int i = 0; i < lane->n_logs; i++) {
        log_draw(lane->logs[i], data);
    }
}

bool waterlane_check_player_on_log(waterlane* lane, player* player) {
    aabb player_collider = player->collider;

    if (player->posy != lane->row) {
        return false;
    }

    for (int i = 0; i < lane->n_logs; i++) {
        aabb log_collider = lane->logs[i]->collider;

        if (aabb_colliding(&player_collider, &log_collider)) {
            return true;
        }
    }
    return false;
}

log* waterlane_get_colliding_log(waterlane* lane, player* player) {
    aabb player_collider = player->collider;

    if (player->posy != lane->row) {
        return NULL;
    }

    for (int i = 0; i < lane->n_logs; i++) {
        aabb log_collider = lane->logs[i]->collider;

        if (aabb_colliding(&player_collider, &log_collider)) {
            return lane->logs[i];
        }
    }
    return NULL;
}

void waterlane_destroy(waterlane* lane) {
    for (int i = 0; i < lane->n_logs; i++) {
        free(lane->logs[i]);
    }
    free(lane);
}
