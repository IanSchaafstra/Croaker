#pragma once
#include "../entities/car.h"

struct carlane {
    car* cars[16];
    int row;
    direction dir;
    int n_cars;
};
typedef struct carlane carlane;

carlane* carlane_init(const env_data* data, int row);
void carlane_update(carlane* lane, const env_data* data);
void carlane_draw(carlane* lane, const env_data* data);

void carlane_destroy(carlane* lane);