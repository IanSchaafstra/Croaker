#pragma once

#define PLAYER_SIZE_Y 3
#define PLAYER_SIZE_X 4

#include "../components/aabb.h"
#include "../structs/config.h"

typedef struct env_data env_data;
typedef struct log log;

struct player {
    int posx, posy;
    int prevposx, prevposy;
    int start_lane;
    aabb collider;

    log* on_log;
    int log_offset;
    lanetype curr_lane;
    lanetype prev_lane;
    int input;
};
typedef struct player player;

player* player_init(const env_data* data);
void player_update(player* player, const env_data* data);
void player_draw(player* player);
void player_update_aabb(player* player);
void player_set_on_log(player* player, log* log);
void player_clear_log(player* player);
void player_set_input(player* player, int input);
