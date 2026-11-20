#pragma once

#include "../../components/direction.h"

struct carconfig {
    int row, col;
    direction dir;
    double cooldown;
};
typedef struct carconfig carconfig;