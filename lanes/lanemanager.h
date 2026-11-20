#pragma once

#include <stdbool.h>

#include "../structs/env_data.h"

#define LANE_HEIGHT 3

typedef struct carlane carlane;
typedef struct waterlane waterlane;
typedef struct grasslane grasslane;
typedef struct scoreboard scoreboard;

typedef struct player player;

struct lanemanager {
    carlane* carlanes[16];
    waterlane* waterlanes[16];
    grasslane* grasslanes[16];
    scoreboard* board;
    player* player;

    int n_carlanes, n_waterlanes, n_grasslanes;
    int curr_row;
};
typedef struct lanemanager lanemanager;
typedef enum lanetype lanetype;

lanemanager* manager_init(const env_data* data);
void manager_regenerate(lanemanager* manager, const env_data* data);
void manager_add_carlane(lanemanager* manager, const env_data* data);
void manager_add_waterlane(lanemanager* manager, const env_data* data);
void manager_add_grasslane(lanemanager* manager, const env_data* data);

void manager_update(lanemanager* manager, const env_data* data);
void manager_draw(lanemanager* manager, const env_data* data);

void manager_set_player_lanetype(lanemanager* manager);
void manager_set_player_input(lanemanager* manager, int input);
void manager_wrap_around(lanemanager* manager);

bool manager_is_player_car_colliding(lanemanager* manager);
void manager_set_player_on_log(lanemanager* manager);
lanetype manager_player_on_lanetype(lanemanager* manager);
bool manager_is_game_over(lanemanager* manager);

void lanemanager_destroy(lanemanager* manager);