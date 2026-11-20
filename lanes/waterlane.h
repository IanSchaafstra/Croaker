#pragma once

#include "../entities/log.h"

struct waterlane {
    log* logs[16];
    int row;
    direction dir;
    int n_logs;
};
typedef struct waterlane waterlane;
typedef struct player player;

waterlane* waterlane_init(const env_data* data, int row);
void waterlane_update(waterlane* lane, const env_data* data);
void waterlane_draw(waterlane* lane, const env_data* data);
bool waterlane_check_player_on_log(waterlane* lane, player* player);
log* waterlane_get_colliding_log(waterlane* lane, player* player);

void waterlane_destroy(waterlane* lane);