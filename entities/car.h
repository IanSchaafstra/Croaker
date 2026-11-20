#pragma once

#include <time.h>

#include "../components/aabb.h"
#include "../components/direction.h"
#include "../structs/configs/carconfig.h"

#define CAR_COOLDOWN 200 // ms
#define CAR_SIZE_X 12
#define CAR_SIZE_Y 3

typedef struct env_data env_data;

enum carcolor {
    CAR_RED,
    CAR_MAGENTA,
    CAR_BLUE,
};
typedef enum carcolor carcolor;

struct car {
    int posx, posy;
    int prevposx, prevposy;
    aabb collider;
    struct timespec s_time, d_time;
    long cooldown;
    direction dir;
    carcolor color;
};
typedef struct car car;


car* car_init_from_config(const carconfig* config);
void car_update(car* car, const env_data* data);
void car_draw(car* car, const env_data* data);
void car_update_aabb(car* car);
void car_sprite_draw(car* car, const env_data* data);