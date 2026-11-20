#include "carlane.h"

#include <stdlib.h>
#include "ncurses.h"
#include "../util/colors.h"
#include "../structs/env_data.h"

carlane* carlane_init(const env_data* data, int row) {
    carlane* lane = malloc(sizeof(carlane));

    int max_entities;
    if ((CAR_SIZE_X + 15) * 2 > data->cols) { // for very narrow terminals
        max_entities = 2;
    } else {
        max_entities = (data->cols / (CAR_SIZE_X + 15));
    }

    lane->row = row;
    int direction = rand() % 2;
    if (direction == 0) {
        lane->dir = RIGHT;
    } else {
        lane->dir = LEFT;
    }

    lane->n_cars = rand() % max_entities + max_entities / 2;
    if (lane->n_cars > 16) {
        lane->n_cars = 16;
    }
    for (int i = 0; i < lane->n_cars; i++) {
        int offset = rand() % 12 + 2;
        int car_pos_x = data->cols / lane->n_cars * i + offset;
        carconfig conf;
        conf.col = car_pos_x;
        conf.row = row;
        conf.cooldown = CAR_COOLDOWN;
        conf.dir = lane->dir;
        car* c = car_init_from_config(&conf);
        lane->cars[i] = c;
    }

    return lane;
}

void carlane_update(carlane* lane, const env_data* data) {
    for (int i = 0; i < lane->n_cars; i++) {
        car_update(lane->cars[i], data);
    }
}

void carlane_draw(carlane* lane, const env_data* data) {
    int stripe_len = 0;
    int empty_spaces = 0;
    for (int i = 0; i < data->cols; i++) {
        attron(COLOR_PAIR(ROAD_COLOR));
        move(lane->row, i);
        addch(' ');
        move(lane->row + 2, i);
        addch(' ');
        attroff(COLOR_PAIR(ROAD_COLOR));
        if (empty_spaces > 0) {
            attron(COLOR_PAIR(ROAD_COLOR));
            empty_spaces--;
        } else if (stripe_len > 0) {
            attron(COLOR_PAIR(ROAD_STRIPE_COLOR));
            stripe_len--;
        } else {
            stripe_len = 6;
            empty_spaces = 5;
        }
        move(lane->row + 1, i);
        addch(' ');
        attroff(COLOR_PAIR(ROAD_STRIPE_COLOR));
    }
    for (int i = 0; i < lane->n_cars; i++) {
        car_draw(lane->cars[i], data);
    }
}

void carlane_destroy(carlane* lane) {
    for (int i = 0; i < lane->n_cars; i++) {
        free(lane->cars[i]);
    }
    free(lane);
}