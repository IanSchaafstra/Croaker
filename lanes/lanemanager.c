#include "lanemanager.h"

#include <stdlib.h>

#include "carlane.h"
#include "grasslane.h"
#include "waterlane.h"
#include "../entities/player.h"
#include "../entities/scoreboard.h"
#include "../structs/config.h"

lanemanager* manager_init(const env_data* data) {
    lanemanager* manager = malloc(sizeof(lanemanager));
    manager->curr_row = 0;
    manager->n_carlanes = manager->n_grasslanes = manager->n_waterlanes = 0;
    manager->board = scoreboard_init(data);
    manager->player = player_init(data);
    int lane_count = (data->rows - (data->rows % LANE_HEIGHT)) / LANE_HEIGHT;

    lane_count -= 3;

    for (int i = 0; i < lane_count; i++) {
        manager->curr_row += LANE_HEIGHT;
        int lane_type = rand() % 3;
        switch (lane_type) {
            case 0:
                manager_add_carlane(manager, data);
                break;
            case 1:
                manager_add_waterlane(manager, data);
                break;
            case 2:
                 manager_add_grasslane(manager, data);
                 break;
            default:
                break;
        }
    }
    for (int i = 0; i < 2; i++) {
        manager->curr_row += LANE_HEIGHT;
        manager_add_grasslane(manager, data);
    }
    if (manager->curr_row < data->rows) {
        manager->curr_row += LANE_HEIGHT;
        manager_add_grasslane(manager, data);
    }

    return manager;
}

void manager_regenerate(lanemanager* manager, const env_data* data) {
    for (int i = 0; i < manager->n_carlanes; i++) {
        carlane_destroy(manager->carlanes[i]);
    }
    for (int i = 0; i < manager->n_waterlanes; i++) {
        waterlane_destroy(manager->waterlanes[i]);
    }
    for (int i = 0; i < manager->n_grasslanes; i++) {
        free(manager->grasslanes[i]);
    }
    manager->player->on_log = NULL;
    manager->curr_row = 0;
    manager->n_carlanes = manager->n_grasslanes = manager->n_waterlanes = 0;
    int lane_count = (data->rows - (data->rows % LANE_HEIGHT)) / LANE_HEIGHT;

    if (lane_count > 3) {
        lane_count -= 3;
    }

    for (int i = 0; i < lane_count; i++) {
        manager->curr_row += LANE_HEIGHT;
        int lane_type = rand() % 3;
        switch (lane_type) {
            case 0:
                manager_add_carlane(manager, data);
                break;
            case 1:
                manager_add_waterlane(manager, data);
                break;
            case 2:
                manager_add_grasslane(manager, data);
                break;
            default:
                break;
        }
    }

    for (int i = 0; i < 2; i++) {
        manager->curr_row += LANE_HEIGHT;
        manager_add_grasslane(manager, data);
    }
}

void manager_add_carlane(lanemanager* manager, const env_data* data) {
    if (manager->n_carlanes < 16) {
        carlane* lane = carlane_init(data, manager->curr_row);
        manager->carlanes[manager->n_carlanes] = lane;
        manager->n_carlanes++;
    }
}

void manager_add_waterlane(lanemanager* manager, const env_data* data) {
    if (manager->n_waterlanes < 16) {
        waterlane* waterlane = waterlane_init(data, manager->curr_row);
        manager->waterlanes[manager->n_waterlanes] = waterlane;
        manager->n_waterlanes++;
    }
}

void manager_add_grasslane(lanemanager* manager, const env_data* data) {
    if (manager->n_grasslanes < 16) {
        grasslane* grasslane = grasslane_init(manager->curr_row);
        manager->grasslanes[manager->n_grasslanes] = grasslane;
        manager->n_grasslanes++;
    }
}

void manager_update(lanemanager* manager, const env_data* data) {
    for (int i = 0; i < manager->n_carlanes; i++) {
        carlane_update(manager->carlanes[i], data);
    }

    for (int i = 0; i < manager->n_waterlanes; i++) {
        waterlane_update(manager->waterlanes[i], data);
    }

    manager_set_player_on_log(manager);
    manager_set_player_lanetype(manager);
    player_update(manager->player, data);
    scoreboard_update(manager->board, data);
    scoreboard_update_pos_mark(manager->board, manager->player->posy);

    if (manager->player->posy < 2) {
        manager_wrap_around(manager);
        manager_regenerate(manager, data);
    }
}

void manager_draw(lanemanager* manager, const env_data* data) {
    for (int i = 0; i < manager->n_carlanes; i++) {
        carlane_draw(manager->carlanes[i], data);
    }
    for (int i = 0; i < manager->n_grasslanes; i++) {
        grasslane_draw(manager->grasslanes[i], data);
    }
    for (int i = 0; i < manager->n_waterlanes; i++) {
        waterlane_draw(manager->waterlanes[i], data);
    }

    scoreboard_draw(manager->board, data);
    player_draw(manager->player);
}

void manager_set_player_lanetype(lanemanager* manager) {
    manager->player->prev_lane = manager->player->curr_lane;
    manager->player->curr_lane = manager_player_on_lanetype(manager);
}

void manager_set_player_input(lanemanager* manager, int input) {
    player_set_input(manager->player, input);
}

void manager_wrap_around(lanemanager* manager) {
    manager->player->posy = manager->player->start_lane;
    manager->board->pos_mark = manager->player->posy;
}

bool manager_is_player_car_colliding(lanemanager* manager) {
    aabb player_aabb = manager->player->collider;

    for (int i = 0; i < manager->n_carlanes; i++) {
        carlane* lane = manager->carlanes[i];

        for (int j = 0; j < lane->n_cars; j++) {
            if (aabb_colliding(&player_aabb, &lane->cars[j]->collider)) {
                return true;
            }
        }
    }
    return false;
}

void manager_set_player_on_log(lanemanager* manager) {
    log* colliding_log = NULL;
    for (int i = 0; i < manager->n_waterlanes; i++) {
        if (waterlane_check_player_on_log(manager->waterlanes[i], manager->player)) {
            colliding_log = waterlane_get_colliding_log(manager->waterlanes[i], manager->player);
            break;
        }
    }

    if (colliding_log != NULL) {
        player_set_on_log(manager->player, colliding_log);
    } else {
        player_clear_log(manager->player);
    }
}

lanetype manager_player_on_lanetype(lanemanager* manager) {
    int player_y = manager->player->posy;


    for (int i = 0; i < manager->n_waterlanes; i++) {
        if (manager->waterlanes[i]->row == player_y) {
            return WATER;
        }
    }

    for (int i = 0; i < manager->n_grasslanes; i++) {
        if (manager->grasslanes[i]->row == player_y) {
            return GRASS;
        }
    }

    for (int i = 0; i < manager->n_carlanes; i++) {
        if (manager->carlanes[i]->row == player_y) {
            return CAR;
        }
    }

    return NONE;
}

bool manager_is_game_over(lanemanager* manager) {
    if (manager_is_player_car_colliding(manager)) {
        return true;
    }


    log* colliding_log = NULL;
    for (int i = 0; i < manager->n_waterlanes; i++) {
        if (waterlane_check_player_on_log(manager->waterlanes[i], manager->player)) {
            colliding_log = waterlane_get_colliding_log(manager->waterlanes[i], manager->player);
            break;
        }
    }
    if (colliding_log == NULL && manager_player_on_lanetype(manager) == WATER) {
        return true;
    }

    return false;
}

void lanemanager_destroy(lanemanager* manager) {
    for (int i = 0; i < manager->n_carlanes; i++) {
        carlane_destroy(manager->carlanes[i]);
    }

    for (int i = 0; i < manager->n_waterlanes; i++) {
        waterlane_destroy(manager->waterlanes[i]);
    }

    for (int i = 0; i < manager->n_grasslanes; i++) {
        free(manager->grasslanes[i]);
    }

    free(manager->board);
    free(manager->player);

    free(manager);
}