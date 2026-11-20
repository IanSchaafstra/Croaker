#include "car.h"
#include "../structs/env_data.h"
#include "../util/colors.h"
#include "../util/array_utils.h"

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "player.h"
#include "../structs/sprites.h"
#include "../util/time_utils.h"


car* car_init_from_config(const carconfig* conf) {
    car* c = malloc(sizeof(car));

    c->posy = conf->row;
    c->posx = conf->col;

    clock_gettime(CLOCK_MONOTONIC, &c->s_time);
    clock_gettime(CLOCK_MONOTONIC, &c->d_time);
    c->dir = conf->dir;

    c->cooldown = conf->cooldown;

    int color = rand() % 3;

    switch (color) {
        case 0:
            c->color = CAR_RED;
            break;
        case 1:
            c->color = CAR_MAGENTA;
            break;
        default:
            c->color = CAR_BLUE;
            break;
    }

    c->collider.posx = c->prevposx = c->posx;
    c->collider.posy = c->prevposy = c->posy;
    c->collider.sizex = CAR_SIZE_X - 1;
    c->collider.sizey = CAR_SIZE_Y - 1;
    return c;
}

void car_update(car* car, const env_data* data) {
    clock_gettime(CLOCK_MONOTONIC, &car->d_time);
    car->prevposx = car->posx;
    car->prevposy = car->posy;

    long diff_ms = (car->d_time.tv_sec - car->s_time.tv_sec) * 1000L + (car->d_time.tv_nsec - car->s_time.tv_nsec) / 1000000L;
    while (diff_ms >= car->cooldown) {
        timespec_add_ms(&car->s_time, car->cooldown);
        diff_ms = (car->d_time.tv_sec - car->s_time.tv_sec) * 1000L + (car->d_time.tv_nsec - car->s_time.tv_nsec) / 1000000L;

        if (car->dir == RIGHT) {
            if (car->posx < data->cols) {
                car->posx++;
            } else {
                car->posx = -CAR_SIZE_X;
            }
        } else {
            if (car->posx > -CAR_SIZE_X) {
                car->posx--;
            } else {
                car->posx = data->cols;
            }
        }
    }

    car_update_aabb(car);
}

void car_draw(car* car, const env_data* data) {
    // removing the previous sprite is not necessary because carlane already draws the lane before the cars
    car_sprite_draw(car, data);
}

void car_update_aabb(car* car) {
    car->collider.posx = car->posx;
    car->collider.posy = car->posy;
}

void car_sprite_draw(car* car, const env_data* data) {
    int sprite[CAR_SIZE_Y][CAR_SIZE_X] = SPRITE_CAR;
    if (car->dir == RIGHT) {
        for (int i = 0; i < 3; i++) {
            reverse_array_in_place(sprite[i], CAR_SIZE_X);
        }
    }
    int x = car->posx;
    int y = car->posy;

    for (int row = 0; row < CAR_SIZE_Y; row++) {
        for (int col = 0; col < CAR_SIZE_X; col++) {
            move(row + y, col + x);
            if (!(row + y < 0 || col + x < 0 || row + y >= data->rows || col + x >= data->cols)) {
                switch (sprite[row][col]) {
                    case COLOR_RED:
                        switch (car->color) {
                            case CAR_RED:
                                attron(COLOR_PAIR(CAR_COLOR_RED));
                                break;
                            case CAR_MAGENTA:
                                attron(COLOR_PAIR(CAR_COLOR_MAGENTA));
                                break;
                            case CAR_BLUE:
                                attron(COLOR_PAIR(CAR_COLOR_BLUE));
                                break;
                        }
                        break;
                    case COLOR_GREY:
                        attron(COLOR_PAIR(CAR_TIRE_COLOR));
                        break;
                    case COLOR_BLUE:
                        attron(COLOR_PAIR(CAR_GLASS_COLOR));
                        break;
                    default:
                        break;
                }
                addch(' ');
                attron(COLOR_PAIR(DEFAULT_COLOR));
                attroff(COLOR_PAIR(DEFAULT_COLOR));
            }
        }
    }
}